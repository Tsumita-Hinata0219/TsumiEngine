#include "DemoParticle.h"


/// <summary>
/// 初期化処理
/// </summary>
void DemoParticle::Init()
{
	// パーティクルインスタンス数
	particleInstanceNum_ = 10;
	// パーティクル作成
	particle_ = std::make_shared<GPUParticle>();
	particle_->Init(particleInstanceNum_);

	// エミッター作成
	emitter_ = std::make_unique<GPUParticleEmitter<GpuParticle::SphereEmitter>>();
	emitter_->Create(particle_);
	// エミッターのデータを取得
	emitData_ = emitter_->GetEmitData();
}


/// <summary>
/// 更新処理
/// </summary>
void DemoParticle::Update()
{
	emitter_->Emit();
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
