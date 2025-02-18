#include "EnemyBulletContainer.h"
#include "../Enemy/IEnemy.h"



/// <summary>
/// コンストラクタ
/// </summary>
EnemyBulletContainer::EnemyBulletContainer()
{
	

}


/// <summary>
/// 初期化処理
/// </summary>
void EnemyBulletContainer::Init(enemy::ShotFuncData data)
{
	// バレットの新スタンスを予め作っておく
	bulletPool_.Create(50);

	// 射撃タイマーの設定 & スタート
	shotTimer_.Init(0.0f, data.shotInterval);
	shotTimer_.Start();
}


/// <summary>
/// 更新処理
/// </summary>
void EnemyBulletContainer::Update()
{
	// タイマー更新・終了してもループ
	shotTimer_.Update(true);

	// タイマー終了で射撃
	if (shotTimer_.IsFinish()) {
		
	}


	// Bulletの更新
	for (EnemyBullet* bullet : bulletList_) {
		bullet->Update();
	}
	bulletList_.remove_if([this](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			// リセット処理
			bullet->Reset();
			bulletPool_.Return(bullet);
			return true;
		}
		return false;
		}
	);
}


/// <summary>
/// 描画処理
/// </summary>
void EnemyBulletContainer::Draw()
{
	for (EnemyBullet* bullet : bulletList_) {
		bullet->Update();
	}
}


/// <summary>
/// バレット追加
/// </summary>
void EnemyBulletContainer::AddBulletInstance(Vector3 initPos, Vector3 initVel, bool isState)
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
/// 射撃ステートの取得
/// </summary>
std::unordered_map<std::string_view, std::function<std::unique_ptr<IEnemyExecuteShot>()>> EnemyBulletContainer::CreateShootingStateFactory()
{
	return {
		{"NONE", []() {return std::make_unique<EnemyShotCross>(); }},
		{"FORWARD", []() {return std::make_unique<EnemyShotForward>(); }},
		{"TRIPLE_FORWARD", []() {return std::make_unique<EnemyShotTripleForward>(); }},
		{"CROSS", []() {return std::make_unique<EnemyShotCross>(); }},
		{"OMNI_FOUR", []() {return std::make_unique<EnemyShotOmniFour>(); }},
		{"OMNI_FIVE", []() {return std::make_unique<EnemyShotOmniFour>(); }},
		{"OMNI_EIGHT", []() {return std::make_unique<EnemyShotOmniFour>(); }},
		{"RANDOM", []() {return std::make_unique<EnemyShotRandom>(); }},
	};
}
