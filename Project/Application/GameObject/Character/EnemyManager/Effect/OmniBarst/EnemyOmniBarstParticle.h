#pragma once

#include "GameObject/GameObject.h"


class EnemyOmniBarstParticle {

public:

	EnemyOmniBarstParticle() = default;
	~EnemyOmniBarstParticle() = default;

	void Init();

	void Update();

	void Draw();
	
	void Emit();

	void SetEmitPos(Vector3 setPos);

	void ReLoad_ParticlePrope();

private:

	std::unique_ptr<Emitter::SphereEmitter> emitter_;
	std::unique_ptr<GpuField::ConstantField> field_;


	std::weak_ptr<LuaScript> particlePropeLua_;
};