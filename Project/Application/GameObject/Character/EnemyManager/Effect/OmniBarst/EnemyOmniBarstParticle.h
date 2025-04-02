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


	void ReLoad_EmitData();
	void ReLoad_RangeData();
	void ReLoad_ComfigData();
	void ReLoad_FieldData();

private:

	std::unique_ptr<Emitter::SphereEmitter> emitter_;
	std::unique_ptr<GpuField::ConstantField> field_;


	std::weak_ptr<LuaScript> lua_;
	std::weak_ptr<LuaScript> sEmitLua_;
	std::weak_ptr<LuaScript> rangeLua_;
	std::weak_ptr<LuaScript> configLua_;
	std::weak_ptr<LuaScript> cFieldLua_;
};