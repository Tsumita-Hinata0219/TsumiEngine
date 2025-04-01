#pragma once

#include "GameObject/GameObject.h"


class EnemyOmniExplosionParticle {

public:

	EnemyOmniExplosionParticle() = default;
	~EnemyOmniExplosionParticle() = default;

	void Init();

	void Update();

	void Draw();

	void Emit();

	void SetEmitPos(Vector3 setPos);

private:

	std::unique_ptr<Emitter::SphereEmitter> emitter_;
	std::unique_ptr<GpuField::ConstantField> field_;


	std::weak_ptr<LuaScript> lua_;
	std::weak_ptr<LuaScript> sEmitLua_;
	std::weak_ptr<LuaScript> rangeLua_;
	std::weak_ptr<LuaScript> configLua_;
	std::weak_ptr<LuaScript> cFieldLua_;
};