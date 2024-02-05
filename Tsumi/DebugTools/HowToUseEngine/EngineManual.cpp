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

	emitter_.worldTransform.Initialize();
	emitter_.worldTransform.translate.x = 0.0f;
	emitter_.count = 10;
	emitter_.frequency = 1.0f * 60.0f;
	emitter_.frequencyTime = 0;

	lifeTimeScope_ = {
		.min = 1,
		.max = 3,
	};
	posScope_ = {
		.X = {-0.5, 0.5f},
		.Y = {-0.5, 0.5f},
		.Z = {0.0f, 0.0f},
	};
	velScope_ = {
		.X = {-1.0f, 1.0f},
		.Y = {-1.0f, 1.0f},
		.Z = {-1.0f, 1.0f},
	};
	colorScope_ = {
		.X = {0.0f, 256.0f},
		.Y = {0.0f, 256.0f},
		.Z = {0.0f, 256.0f},
		.W = {256.0f, 256.0f},
	};
	particle_->Initialize(new ParticlePlane(), emitter_.count);
}


/// <summary>
/// 更新処理
/// </summary>
void EngineManual::Update(ViewProjection view) 
{
	emitter_.frequencyTime += 1.0f;

	if (emitter_.frequencyTime >= emitter_.frequency) {
		emitter_.frequencyTime = 0.0f;
		particle_->Emit(emitter_, lifeTimeScope_, posScope_, velScope_, colorScope_);
	}

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
	particle_->Draw(circleHD_, view);
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