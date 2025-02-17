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


	transforms_.resize(particleInstanceNum_);
	for (auto& element : transforms_) {
		element.Init();
		element.srt.translate.z = 5.0f;
	}
	materials_.resize(particleInstanceNum_);
	for (auto& element : materials_) {
		element.color = Temp::Color::WHITE;
		element.uvTransform = Matrix4x4::identity;
	}
}


/// <summary>
/// 更新処理
/// </summary>
void DemoParticle::Update()
{

	emitter_->Emit(particle_);
	emitter_->Update();
}


/// <summary>
/// 描画処理
/// </summary>
void DemoParticle::Draw()
{
	/* ----- DemoParticle デモパーティクル ----- */
	particle_->Draw(transforms_, materials_);
}
