#include "EnemyManager.h"
#include "../Player/Player.h"


/// <summary>
/// 初期化処理
/// </summary>
void EnemyManager::Init()
{
	// エネミー関連のモデルの読み込み
	modelManager_ = ModelManager::GetInstance();
	modelManager_->LoadModel("Obj/Enemys/Bullet", "EnemyBullet.obj");

	// Transformの初期化
	transform_.Init();
	transform_.srt.translate.z = 30.0f;

	// BulletのPoolのインスタンスを先に作っておく
	bulletPool_.Create(100);

	// EffectのPoolのインスタンスを先に作っておく
	circleEffectPool_.Create(100);

	// EnemyListの更新処理
	for (auto& enemy : enemys_) {
		enemy->Update();
	}

	// エネミーが全滅したかのフラグは折っておく
	isEliminated_ = false;
}


/// <summary>
/// 更新処理
/// </summary>
void EnemyManager::Update()
{
	// 全滅していたら処理を通さない
	if (isEliminated_) { return; }

	// EnemyListの更新処理
	for (auto& enemy : enemys_) {
		enemy->Update();
	}
	// 死亡フラグが立っていたら削除
	enemys_.remove_if([](std::unique_ptr<IEnemy>& enemy) {
		if (enemy->IsDead()) {
			return true;
		}
		return false;
		}
	);

	// Bulletの更新処理
	for (EnemyBullet* bullet : bulletList_) {
		bullet->Update();
	}
	// 死亡した弾丸を整理し、プールに返却
	bulletList_.remove_if([this](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			// リセット処理を入れておく
			bullet->Reset();
			bulletPool_.Return(bullet);
			return true;
		}
		return false;
		}
	);

	// Effectの更新処理
	for (EnemyHitEffectCircle* effect : circleEffectList_) {
		effect->Update();
	}
	// 死亡フラグが立っていたら削除
	circleEffectList_.remove_if([this](EnemyHitEffectCircle* effect) {
		if (effect->IsDead()) {
			// 死亡したエフェクトはプールに返却
			circleEffectPool_.Return(effect);
			return true;
		}
		return false;
		}
	);

	// 全滅したかのチェック
	EliminatedChecker();


#ifdef _DEBUG
	DrawimGui();
#endif // _DEBUG
}


/// <summary>
/// 描画処理
/// </summary>
void EnemyManager::Draw3D()
{
	// EnemyListの描画
	for (auto& enemy : enemys_) {
		enemy->Draw3D();
	}

	// Bulletsの描画
	for (EnemyBullet* bullet : bulletList_) {
		bullet->Draw3D();
	}

	// Effectの描画
	for (EnemyHitEffectCircle* effect : circleEffectList_) {
		effect->Draw3D();
	}
}


/// <summary>
/// Jsonで読み込んだ情報を受け取る
/// </summary>
void EnemyManager::LoadEntityData(const std::vector<std::unique_ptr<EntityData>>& datas)
{
	for (const auto& entityData : datas) {
		if (entityData) {

			if (entityData->entityName == "BasicEnemy") {
				CreateBasicEnemy(*entityData.get());
			}
			else if (entityData->entityName == "StaticEnemy") {
				CreateStaticEnemy(*entityData.get());
			}
			else if (entityData->entityName == "BossEnemy") {
				CreateBossEnemy(*entityData.get());
			}
		}
	}
}


/// <summary>
/// 新しいEnemyBulletを追加する
/// </summary>
void EnemyManager::AddNewBullet(Vector3 initPos, Vector3 initVel, bool isState)
{
	CreateEnemyBullet(initPos, initVel, isState);
}


/// <summary>
/// 新しいヒットエフェクトを追加する
/// </summary>
void EnemyManager::AddNewHitEffect(IEnemy* enemyPtr)
{
	CreateEffect(enemyPtr);
}


/// <summary>
/// 全滅したかのチェック
/// </summary>
void EnemyManager::EliminatedChecker()
{
	int instanceNum = int(enemys_.size());

	// インスタンスが0なので全滅フラグを立てる
	if (instanceNum <= 0) {
		isEliminated_ = true;
	}
}


/// <summary>
/// 新しいEnemyを生成する
/// </summary>
void EnemyManager::CreateBasicEnemy(const EntityData& setEntityData)
{
	// 新しいEnemyのインスタンス
	std::unique_ptr<BasicEnemy> newEnemy = std::make_unique<BasicEnemy>();

	// newEnemyの初期化
	newEnemy->SetPlayer(this->player_);
	newEnemy->SetEnemyManager(this);
	newEnemy->SetShotProperty(setEntityData.enemyData.shotFuncData);
	newEnemy->SetMovementProperty(setEntityData.enemyData.movementFuncData);
	newEnemy->SetInitSRT(setEntityData.srt);
	newEnemy->Init();

	// リストに追加
	enemys_.push_back(std::move(newEnemy));
}
void EnemyManager::CreateStaticEnemy(const EntityData& setEntityData)
{
	// 新しいEnemyのインスタンス
	std::unique_ptr<StaticEnemy> newEnemy = std::make_unique<StaticEnemy>();

	// newEnemyの初期化
	newEnemy->SetPlayer(this->player_);
	newEnemy->SetEnemyManager(this);
	newEnemy->SetShotProperty(setEntityData.enemyData.shotFuncData);
	newEnemy->SetMovementProperty(setEntityData.enemyData.movementFuncData);
	newEnemy->SetInitSRT(setEntityData.srt);
	newEnemy->Init();

	// リストに追加
	enemys_.push_back(std::move(newEnemy));
}
void EnemyManager::CreateBossEnemy(const EntityData& setEntityData)
{
	// 新しいEnemyのインスタンス
	std::unique_ptr<BossEnemy> newEnemy = std::make_unique<BossEnemy>();

	// newEnemyの初期化
	newEnemy->SetPlayer(this->player_);
	newEnemy->SetEnemyManager(this);
	newEnemy->SetShotProperty(setEntityData.enemyData.shotFuncData);
	newEnemy->SetMovementProperty(setEntityData.enemyData.movementFuncData);
	newEnemy->SetInitSRT(setEntityData.srt);
	newEnemy->Init();

	// リストに追加
	enemys_.push_back(std::move(newEnemy));
}


/// <summary>
/// 新しいEnemyBulletを生成する
/// </summary>
void EnemyManager::CreateEnemyBullet(Vector3 initPos, Vector3 initVel, bool isState)
{
	// オブジェクトプールから新しいバレットを取得
	EnemyBullet* newBullet = bulletPool_.Get();

	// newBulletの初期化
	newBullet->SetResistant(isState);
	newBullet->Init();
	newBullet->SetPosition(initPos);
	newBullet->SetVelocity(initVel);
	newBullet->SetRotationFromVelocity();

	// リストに追加
	bulletList_.push_back(newBullet);
}


/// <summary>
/// 新しいEffectを生成する
/// </summary>
void EnemyManager::CreateEffect(IEnemy* enemyPtr)
{
	// プールから新しいエフェクトを取得
	EnemyHitEffectCircle* newEffect = circleEffectPool_.Get();

	// newEffectの初期化
	newEffect->SetEnemyPtr(enemyPtr);
	newEffect->Init();

	// リストに追加
	circleEffectList_.push_back(newEffect);
}


/// <summary>
/// ImGuiの描画
/// </summary>
void EnemyManager::DrawimGui()
{
	if (ImGui::TreeNode("EnemyManager")) {

		ImGui::Text("Transform");
		ImGui::DragFloat3("Scale", &transform_.srt.scale.x, 0.01f, 0.0f, 20.0f);
		ImGui::DragFloat3("Rotate", &transform_.srt.rotate.x, 0.01f);
		ImGui::DragFloat3("Translate", &transform_.srt.translate.x, 0.1f);
		ImGui::Text("");

		ImGui::Text("IEnemyInstance = %d", int(enemys_.size()));
		ImGui::Text("");

		ImGui::Text("Bullet");
		int instance = int(bulletList_.size());
		ImGui::DragInt("Bullet_InstanceSize", &instance, 0);
		ImGui::Text("");

		ImGui::TreePop();
	}
}

