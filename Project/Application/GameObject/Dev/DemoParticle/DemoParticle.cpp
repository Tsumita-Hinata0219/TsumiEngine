#include "DemoParticle.h"


/// <summary>
/// 初期化処理
/// </summary>
void DemoParticle::Init()
{
	particleInstanceNum_ = 10;
	particle_ = std::make_unique<GPUParticle>();
	particle_->Init(particleInstanceNum_);

	emitter_ = std::make_unique<GPUParticleEmitter<GpuParticle::SphereEmitter>>();
	emitter_->Create(particle_);

}


/// <summary>
/// 更新処理
/// </summary>
void DemoParticle::Update()
{
	emitter_->Emit(particle_);
	emitter_->Update();
	particle_->Update();
}


/// <summary>
/// 描画処理
/// </summary>
void DemoParticle::Draw()
{
	/* ----- DemoParticle デモパーティクル ----- */
	particle_->Draw();
}

