#pragma once

#include "GameObject.h"

class Photon {

public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ViewProjection view);

private:

	// テクスチャハンドル
	uint32_t circleHD_;

	// Particle
	std::unique_ptr<Particle> particle_ = nullptr;

	// パーティクルリスト
	std::list<ParticleProperties> particlePropes_{};

	// エミッター
	Emitter emitter_{};

	// スコープ
	Scope lifeTimeScope_{};
	ScopeVec3 posScope_{};
	ScopeVec3 velScope_{};
	ScopeVec4 colorScope_{};
};

