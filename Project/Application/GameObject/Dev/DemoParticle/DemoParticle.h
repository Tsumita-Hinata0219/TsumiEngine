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

	// Particle
	std::shared_ptr<GPUParticle> particle_;

	// Emitter
	std::unique_ptr<GPUParticleEmitter<GpuEmitter::SphereEmitter>> emitter_;
	// Emit Data
	std::weak_ptr<GpuEmitter::SphereEmitter> emitData_;

	// Emit Config
	std::weak_ptr<GpuEmitter::EmitterConfig> emitConfig_;

	// Emit Range
	std::weak_ptr<GpuEmitter::EmitterRange> emitRange_;

	// Field
	std::unique_ptr<GPUParticleField<GpuField::ConstantField>> field_;
	// Field Data
	std::weak_ptr<GpuField::ConstantField> fieldData_;

};