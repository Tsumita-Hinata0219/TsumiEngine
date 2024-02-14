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

	// Particle
	std::unique_ptr<Particle> particle_ = nullptr;

	uint32_t circleHD_;

	// パーティクルリスト
	std::list<ParticleProperties> particlePropes_{};
	Emitter emitter_{};
	Scope lifeTimeScope_{};
	ScopeVec3 posScope_{};
	ScopeVec3 velScope_{};
	ScopeVec4 colorScope_{};
};

