#pragma once

#include "GameObject/GameObject.h"


/* デモパーティクル */
class DemoParticle {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	DemoParticle();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~DemoParticle();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();


private:

	// DemoParticle
	uint32_t particleInstanceNum_ = 0;
	std::unique_ptr<GPUParticle> particle_;
	std::unique_ptr<GPUParticleEmitter<GpuParticle::SphereEmitter>> emitter_;

	std::vector<Transform> transforms_;
	std::vector<MaterialDataN> materials_;
};