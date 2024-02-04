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
	circleHD_ = TextureManager::LoadTexture("circle.png");

	particle_ = make_unique<Particle>();
	particle_->Initialize(new ParticlePlane(), kNumInstanceNum_, circleHD_);
	Scope lifeTimeScope = {
		.min = 1,
		.max = 3,
	};
	ScopeVec3 posScope = {
		.X = {-1.0f, 1.0f},
		.Y = {-1.0f, 1.0f},
		.Z = {0.0f, 0.0f},
	};
	ScopeVec3 velScope = {
		.X = {-1.0f, 1.0f},
		.Y = {-1.0f, 1.0f},
		.Z = {-1.0f, 1.0f},
	};
	ScopeVec4 colorScope = {
		.X = {0.0f, 256.0f},
		.Y = {0.0f, 256.0f},
		.Z = {0.0f, 256.0f},
		.W = {256.0f, 256.0f},
	};
	for (int i = 0; i < kNumInstanceNum_; i++) {

		particlePrope_[i] = Particle::ParticleGenerators(lifeTimeScope, posScope, velScope, colorScope);
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

		// 速度を座標に加算
		prope.worldTransform.translate += prope.velocity;

		// 寿命の処理
		prope.currentTime++;

		// alphaの処理
		float alpha = 1.0f - (float(prope.currentTime) / float(prope.lifeTime));
		prope.color.w = alpha;

		if (prope.currentTime >= prope.lifeTime) {
			continue;
		}

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