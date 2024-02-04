#include "EngineManual.h"



/// <summary>
/// デストラクタ
/// </summary>
EngineManual::~EngineManual() 
{


}


/// <summary>
/// 初期化処理
/// </summary>
void EngineManual::Initialize() 
{
	uvCheckerHD_ = TextureManager::LoadTexture("uvChecker.png");

	particle_ = make_unique<Particle>();
	particle_->Initialize(new ParticlePlane(), NumInstance_, uvCheckerHD_);
	Scope scope = {
		.X = {-2.0f, 2.0f},
		.Y = {-2.0f, 2.0f},
		.Z = Vector2::zero,
	};
	for (int i = 0; i < NumInstance_; i++) {

		particlePrope_[i] = Particle::ParticleGenerators(scope);
		particle_->PushBackList(particlePrope_[i]);
	}
}


/// <summary>
/// 更新処理
/// </summary>
void EngineManual::Update(ViewProjection view) 
{

	particlePropes_ = particle_->RetrieveFront();
	for (ParticleProperties& prope : particlePropes_) {
		prope.worldTransform.translate += prope.velocity;
		particle_->PushBackList(prope);
	}

#ifdef _DEBUG


#endif // _DEBUG

}


/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void EngineManual::BackSpriteDraw(ViewProjection view) 
{


}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void EngineManual::ModelDraw(ViewProjection view) 
{
	particle_->Draw(view);
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void EngineManual::FrontSpriteDraw(ViewProjection view) 
{


}


/// <summary>
/// Audioに関する処理まとめたやつ
/// </summary>
void EngineManual::AudioUpdate() 
{



#ifdef _DEBUG



#endif // _DEBUG
}