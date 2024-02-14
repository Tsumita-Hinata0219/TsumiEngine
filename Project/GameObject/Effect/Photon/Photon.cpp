#include "Photon.h"



// 初期化処理
void Photon::Initialize()
{
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


// 更新処理
void Photon::Update()
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


// 描画処理
void Photon::Draw(ViewProjection view)
{
	particle_->Draw(circleHD_, view);
}
