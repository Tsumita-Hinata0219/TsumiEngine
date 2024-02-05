#include "Photon.h"



// 初期化処理
void Photon::Initialize()
{
	// テクスチャハンドルの読み込み
	circleHD_ = TextureManager::LoadTexture("circle.png");

	// エミッターの初期化
	emitter_.worldTransform.Initialize();
	emitter_.worldTransform.translate.x = 0.0f;
	emitter_.count = 10;
	emitter_.frequency = 1.0f * 60.0f;
	emitter_.frequencyTime = 0;

	// 各スコープの初期化
	lifeTimeScope_ = {
		.min = 2,
		.max = 5,
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
		.X = {256.0f, 256.0f},
		.Y = {256.0f, 256.0f},
		.Z = {256.0f, 256.0f},
		.W = {256.0f, 256.0f},
	};


	// パーティクルの初期化
	particle_ = make_unique<Particle>();
	particle_->Initialize(new ParticlePlane(), emitter_.count);
}


// 更新処理
void Photon::Update()
{
	// 出現頻度のタイマー加算
	emitter_.frequencyTime += 1.0f;

	// タイマーが既定値になったら
	if (emitter_.frequencyTime >= emitter_.frequency) {

		// タイマーを０で代入
		emitter_.frequencyTime = 0.0f;

		// パーティクルの出現
		particle_->Emit(emitter_, lifeTimeScope_, posScope_, velScope_, colorScope_);
	}

	if (KeysInput::TriggerKey(DIK_P)) {
		// パーティクルの出現
		particle_->Emit(emitter_, lifeTimeScope_, posScope_, velScope_, colorScope_);
	}

	// パーティクルリストの取得
	particlePropes_ = particle_->RetrieveFront();

	for (ParticleProperties& prope : particlePropes_) {

		// 速度を座標に加算
		prope.worldTransform.translate += prope.velocity;

		// 寿命の処理
		prope.currentTime++;

		//// alphaの処理
		//float alpha = 1.0f - (float(prope.currentTime) / float(prope.lifeTime));
		//prope.color.w = alpha;

		// 寿命が尽きたらコンティニュー
		if (prope.currentTime >= prope.lifeTime) {
			continue;
		}

		// リストにプッシュバック
		particle_->PushBackList(prope);
	}

}


// 描画処理
void Photon::Draw(ViewProjection view)
{
	particle_->Draw(circleHD_, view);
}
