#pragma once

#include "GameObject/GameObject.h"


/* デモパーティクル */
class DemoParticle {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	DemoParticle() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~DemoParticle() = default;

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

	/// <summary>
	/// ImGui描画
	/// </summary>
	void DrawImGui();


private:

	// DemoParticle
	uint32_t particleInstanceNum_ = 0;

	// パーティクル本体
	std::shared_ptr<GPUParticle> particle_;

	// エミッター
	std::unique_ptr<GPUParticleEmitter<GpuParticle::SphereEmitter>> emitter_;

	// エミッターの情報
	std::weak_ptr<GpuParticle::SphereEmitter> emitData_;

	// エミッターコンフィグ
	std::weak_ptr<GpuParticle::EmitterConfig> emitConfig_;
};