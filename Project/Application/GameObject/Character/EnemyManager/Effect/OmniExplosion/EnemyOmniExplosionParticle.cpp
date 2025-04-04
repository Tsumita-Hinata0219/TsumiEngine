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


	// Luaから値を受け取る
	emitter_->Load_EmitData_From_Lua(sEmitLua_);
	sEmitLua_.lock()->SetReloadCallback([this]() { ReLoad_EmitData(); });

	emitter_->Load_EmitRangeData_From_Lua(rangeLua_);
	rangeLua_.lock()->SetReloadCallback([this]() { ReLoad_RangeData(); });

	emitter_->Load_EmitConfigData_From_Lua(configLua_);
	configLua_.lock()->SetReloadCallback([this]() { ReLoad_ComfigData(); });

	field_->Load_FieldData_From_Lua(cFieldLua_);
	cFieldLua_.lock()->SetReloadCallback([this]() { ReLoad_FieldData(); });
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
	emitter_->Emit();
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

void EnemyOmniExplosionParticle::ReLoad_EmitData()
{
	emitter_->Load_EmitData_From_Lua(sEmitLua_);
}

void EnemyOmniExplosionParticle::ReLoad_RangeData()
{
	emitter_->Load_EmitRangeData_From_Lua(rangeLua_);
}

void EnemyOmniExplosionParticle::ReLoad_ComfigData()
{
	emitter_->Load_EmitConfigData_From_Lua(configLua_);
}

void EnemyOmniExplosionParticle::ReLoad_FieldData()
{
	field_->Load_FieldData_From_Lua(cFieldLua_);
}
