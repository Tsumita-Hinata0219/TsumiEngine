#pragma once

#include "../Interface/IPlayerParticle.h"


/* PlayerのMovement時に出るパーティクル */
class PlayerMovementParticle : public IPlayerParticle {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerMovementParticle() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerMovementParticle() = default;

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

	/// <summary>
	/// Scale値の計算
	/// </summary>
	void CalcScale();


private:

	// タイマー
	Timer timer_{};

	// 補間に使用するAlpha値
	std::pair<float, float> scale_;

	// 速度
	float velocity_ = 0.0f;

};

