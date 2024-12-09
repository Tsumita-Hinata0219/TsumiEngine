#pragma once

#include "../../Interface/IEnemyEffect.h"


/* エネミーのヒットエフェクト */
class EnemyHitEffectCircle : public IEnemyEffect {

public:

	/// <summary>
	/// コンストラク
	/// </summary>
	EnemyHitEffectCircle() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyHitEffectCircle() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw3D() override;


private:


};
