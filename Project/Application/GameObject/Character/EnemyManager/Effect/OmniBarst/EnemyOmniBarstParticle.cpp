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
	sEmitLua_ = luaManager->GetScript("EnemyOmniBarst_SphereEmitter");
	rangeLua_ = luaManager->GetScript("EnemyOmniBarst_EmitterRange");
	configLua_ = luaManager->GetScript("EnemyOmniBarst_EmitConfig");
	cFieldLua_ = luaManager->GetScript("EnemyOmniBarst_ConstantField");


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
	emitter_->Emit();
}

void EnemyOmniBarstParticle::SetEmitPos(Vector3 setPos)
{
	if (auto lokedData = emitter_->GetWeak_EmitData().lock()) {
		Vector4 newPos = {
			setPos.x, setPos.y, setPos.z, 0.0f
		};
		lokedData->translate = newPos;
	}
}


void EnemyOmniBarstParticle::ReLoad_EmitData()
{
	emitter_->Load_EmitData_From_Lua(sEmitLua_);
}

void EnemyOmniBarstParticle::ReLoad_RangeData()
{
	emitter_->Load_EmitRangeData_From_Lua(rangeLua_);
}

void EnemyOmniBarstParticle::ReLoad_ComfigData()
{
	emitter_->Load_EmitConfigData_From_Lua(configLua_);
}

void EnemyOmniBarstParticle::ReLoad_FieldData()
{
	field_->Load_FieldData_From_Lua(cFieldLua_);
}
