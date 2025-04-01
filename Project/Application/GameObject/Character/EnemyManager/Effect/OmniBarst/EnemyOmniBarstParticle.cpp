#include "EnemyOmniBarstParticle.h"

void EnemyOmniBarstParticle::Init()
{
	emitter_ = std::make_unique<Emitter::SphereEmitter>();
	emitter_->Create();
	field_ = std::make_unique<GpuField::ConstantField>();
	field_->Create(emitter_->GetWeak_Particle());
	
	auto luaManager = LuaManager::GetInstance();
	luaManager->LoadScript("LuaScript/EnemyOmniBarst", "EnemyOmniBarst_SphereEmitter.lua");
	luaManager->LoadScript("LuaScript/EnemyOmniBarst", "EnemyOmniBarst_EmitterRange.lua");
	luaManager->LoadScript("LuaScript/EnemyOmniBarst", "EnemyOmniBarst_EmitConfig.lua");
	luaManager->LoadScript("LuaScript/EnemyOmniBarst", "EnemyOmniBarst_ConstantField.lua");
	sEmitLua_ = luaManager->GetScript("Duumy_SphereEmitter");
	rangeLua_ = luaManager->GetScript("Dummy_EmitterRange");
	configLua_ = luaManager->GetScript("Dummy_EmitConfig");
	cFieldLua_ = luaManager->GetScript("Dummy_ConstantField");


	emitter_->Load_EmitData_From_Lua(sEmitLua_);
	emitter_->Load_EmitRangeData_From_Lua(rangeLua_);
	emitter_->Load_EmitConfigData_From_Lua(configLua_);
	field_->Load_FieldData_From_Lua(cFieldLua_);
}

void EnemyOmniBarstParticle::Update()
{
	emitter_->Update();
	field_->Update();
}

void EnemyOmniBarstParticle::Draw()
{
	emitter_->Draw3D();
}

void EnemyOmniBarstParticle::Emit()
{
}
