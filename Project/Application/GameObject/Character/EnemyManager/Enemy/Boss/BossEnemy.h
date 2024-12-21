#pragma once

#include "../IEnemy.h"
#include "GameObject/IObject/IObject.h"
#include "Math/MyMath.h"

#include "../../Bullet/EnemyBullet.h"

/* ボスエネミー */
class BossEnemy : public IEnemy {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	BossEnemy() { attribute_ = { Attributes::Category::ENEMY, Attributes::Type::BODY }; };
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~BossEnemy() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Draw3D() override;
	void Draw2DFront() override;
	void Draw2DBack() override;

	/// <summary>
	/// 衝突判定コールバック関数
	/// </summary>
	void onCollision([[maybe_unused]] IObject* object) override;


#pragma region Accessor アクセッサ



#pragma endregion 


private:



private:



};