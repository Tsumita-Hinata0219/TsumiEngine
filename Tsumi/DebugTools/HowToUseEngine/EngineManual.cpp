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
	particle_->Initialize(new ParticlePlane, NumInstance_);
	for (int i = 0; i < NumInstance_; i++) {

		particlePrope_[i].worldTransform.scale = { 1.0f, 1.0f, 1.0f };
		particlePrope_[i].worldTransform.rotate = { 0.0f, 0.0f, 0.0f };
		particlePrope_[i].worldTransform.translate = {
			i * 0.1f,
			i * 0.1f ,
			i * 0.1f,
		};
		particlePrope_[i].color = { 1.0f, 1.0f, 1.0f, 1.0f };
		particlePrope_[i].velocity = { 0.0f, 1.0f, 0.0f };
		particlePrope_[i].uvTransform.scale = { 1.0f, 1.0f, 1.0f };
		particlePrope_[i].uvTransform.rotate = { 0.0f, 0.0f, 0.0f };
		particlePrope_[i].uvTransform.translate = { 0.0f, 0.0f, 0.0f };

		particle_->PushBackParticles(particlePrope_[i]);
	}

}


/// <summary>
/// 更新処理
/// </summary>
void EngineManual::Update(ViewProjection view) 
{

	particle_->Update();

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