#include "Particle.h"



// 初期化処理
void Particle::Initialize(IParticleState* state, uint32_t instanceNum, uint32_t useTex) {

	// テクスチャの初期設定
	this->useTexture_ = useTex;

	// インスタンス数
	instanceNum_ = instanceNum;

	// ステートパターンの初期化処理
	this->state_ = state;
	state_->Initialize(this);
}


// 描画処理
void Particle::Draw(ViewProjection view) {

	state_->Draw(this, particlePropes_, view);
}


// 先頭から情報を取り出す
list<ParticleProperties> Particle::RetrieveFront()
{
	for (list<ParticleProperties>::iterator itr = particlePropes_.begin(); itr != particlePropes_.end();) {

		if (!(*itr).isActive) {
			particlePropes_.erase(itr);
		}
		else {
			++itr;
		}
	}

	list<ParticleProperties> propes = particlePropes_;
	particlePropes_.clear();
	return propes;
}


// リストの登録
void Particle::PushBackList(ParticleProperties prope) {

	particlePropes_.push_back(prope);
}


// パーティクルの生成器
ParticleProperties Particle::ParticleGenerators(Scope scope)
{
	ParticleProperties particlePrope{};
	particlePrope.worldTransform.Initialize();
	particlePrope.worldTransform.scale = Vector3::one;
	particlePrope.worldTransform.rotate = Vector3::zero;
	particlePrope.worldTransform.translate =
		RandomGenerator::getRandom(scope.X, scope.Y, scope.Z);
	particlePrope.color = Vector4::one;
	particlePrope.velocity = Vector3::oneY / 50.0f;
	particlePrope.uvTransform.scale = Vector3::one;
	particlePrope.uvTransform.rotate = Vector3::zero;
	particlePrope.uvTransform.translate = Vector3::zero;
	particlePrope.isActive = true;

	return particlePrope;
}

