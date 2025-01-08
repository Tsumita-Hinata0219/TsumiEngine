#include "EnemyMovement.h"
#include "../EnemyManager.h"
#include "../Enemy/IEnemy.h"
#include "../../Player/Player.h"


/// <summary>
/// コンストラクタ
/// </summary>
EnemyMovement::EnemyMovement(EnemyManager* manager, IEnemy* owner, Player* player)
{
	this->pManager_ = manager;
	this->pOwner_ = owner;
	this->pPlayer_ = player;
}


/// <summary>
/// 初期化処理
/// </summary>
void EnemyMovement::Init(const enemy::MovementFuncData& data)
{
	data_ = data;

	// 関数設定
	SetMovementFunc(data_.behavior);

	// behaviorがHorizontalなら中間点をOwnerの初期座標で初期化
	if (data_.behavior == enemy::MovementBehavior::Horizontal) {
		data_.horizontal_middle = pOwner_->GetWorldPos();
	}
}


/// <summary>
/// 更新処理
/// </summary>
void EnemyMovement::Update()
{
	// 移動処理
	movementFunc_();

	// フラグが立っていたら
	if (isTilt_) {
		BodyTilt();
	}
}


/// <summary>
/// 移動関数の設定
/// </summary>
void EnemyMovement::SetMovementFunc(enemy::MovementBehavior movement)
{
	switch (movement)
	{
	case enemy::MovementBehavior::Static:
		movementFunc_ = std::bind(&EnemyMovement::Movement_Static, this);
		break;
	case enemy::MovementBehavior::Follow:
		movementFunc_ = std::bind(&EnemyMovement::Movement_Follow, this);
		break;
	case enemy::MovementBehavior::Horizontal:
		movementFunc_ = std::bind(&EnemyMovement::Movement_Horizontal, this);
		break;
	case enemy::MovementBehavior::Circular:
		movementFunc_ = std::bind(&EnemyMovement::Movement_Circular, this);
		break;
	default:
		break;
	}
}


/// <summary>
/// 不動
/// </summary>
void EnemyMovement::Movement_Static() {}


/// <summary>
/// 追従
/// </summary>
void EnemyMovement::Movement_Follow()
{
	// ある程度近ければ早期return
	if (std::abs(Length(pPlayer_->GetWorldPos() - pOwner_->GetWorldPos())) <= minToPlayer_) {
		return;
	}

	// velocityを計算
	// 差分をNormalize
	Vector3 player2Enemy =
		Normalize(pPlayer_->GetWorldPos() - pOwner_->GetWorldPos());

	// 差分Normalizeに速度をかけてvelocityに設定
	Vector3 moveVelocity = {
		player2Enemy.x * data_.velocity,
		player2Enemy.y, // y軸は移動してほしくないのでそのまま
		player2Enemy.z * data_.velocity,
	};

	// 座標にvelocityを加算
	Vector3 setTranslate = pOwner_->GetWorldPos() + moveVelocity;
	pOwner_->SetTranslate(setTranslate);
}


/// <summary>
/// 直線移動
/// </summary>
void EnemyMovement::Movement_Horizontal()
{
}


/// <summary>
/// 円移動
/// </summary> 
void EnemyMovement::Movement_Circular()
{
	static float angle = 0.0f; // 現在の角度を保持

	// 角速度を計算 (velocity に依存)
	angle += data_.velocity; // deltaTime はフレーム間の時間

	// 角度が2πを超えたらリセット
	if (angle > 2.0f * 3.14159265359f) {
		angle -= 2.0f * 3.14159265359f;
	}

	// 新しい位置を計算
	Vector3 setTranslate = {
		data_.circular_center.x + data_.circular_radius * cos(angle),
		pOwner_->GetWorldPos().y,
		data_.circular_center.z + data_.circular_radius * sin(angle),
	};
	pOwner_->SetTranslate(setTranslate);
}


/// <summary>
/// プレイヤーに体を向ける処理
/// </summary>
void EnemyMovement::BodyTilt()
{
	// 差分をNormalize
	Vector3 player2Enemy =
		Normalize(pPlayer_->GetWorldPos() - pOwner_->GetWorldPos());

	// 差分Normalizeに速度をかけてvelocityに設定
	Vector2 direction = {
		player2Enemy.x,
		player2Enemy.z,
	};

	// Y軸周り角度(θy)
	pOwner_->SetRotate_Y(std::atan2(direction.x, direction.y));
}

