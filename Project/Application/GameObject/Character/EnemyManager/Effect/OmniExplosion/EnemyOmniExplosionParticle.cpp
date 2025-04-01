#include "EnemyOmniExplosionParticle.h"

void EnemyOmniExplosionParticle::Init()
{
	emitter_ = std::make_unique<Emitter::SphereEmitter>();
	emitter_->Create();
	field_ = std::make_unique<GpuField::ConstantField>();
	field_->Create(emitter_->GetWeak_Particle());

	auto luaManager = LuaManager::GetInstance();
	luaManager->LoadScript("LuaScript/EnemyOmniExplosion", "EnemyOmniExplosion_SphereEmitter.lua");
	luaManager->LoadScript("LuaScript/EnemyOmniExplosion", "EnemyOmniExplosion_EmitterRange.lua");
	luaManager->LoadScript("LuaScript/EnemyOmniExplosion", "EnemyOmniExplosion_EmitConfig.lua");
	luaManager->LoadScript("LuaScript/EnemyOmniExplosion", "EnemyOmniExplosion_ConstantField.lua");
	sEmitLua_ = luaManager->GetScript("EnemyOmniExplosion_SphereEmitter");
	rangeLua_ = luaManager->GetScript("EnemyOmniExplosion_EmitterRange");
	configLua_ = luaManager->GetScript("EnemyOmniExplosion_EmitConfig");
	cFieldLua_ = luaManager->GetScript("EnemyOmniExplosion_ConstantField");


	emitter_->Load_EmitData_From_Lua(sEmitLua_);
	emitter_->Load_EmitRangeData_From_Lua(rangeLua_);
	emitter_->Load_EmitConfigData_From_Lua(configLua_);
	field_->Load_FieldData_From_Lua(cFieldLua_);
}

void EnemyOmniExplosionParticle::Update()
{
	emitter_->Update();
	field_->Update();
}

void EnemyOmniExplosionParticle::Draw()
{
	emitter_->Draw3D();
}

void EnemyOmniExplosionParticle::Emit()
{
}

void EnemyOmniExplosionParticle::SetEmitPos(Vector3 setPos)
{
	if (auto lokedData = emitter_->GetWeak_EmitData().lock()) {
		Vector4 newPos = {
			setPos.x, setPos.y, setPos.z, 0.0f
		};
		lokedData->translate = newPos;
	}
}
