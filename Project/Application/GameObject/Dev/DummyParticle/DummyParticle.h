#pragma once

#include "GameObject/GameObject.h"



class DummyParticle
{
private:
	std::unique_ptr<Emitter::SphereEmitter> sEmit_;
	std::unique_ptr<GpuField::ConstantField> cField_;
	std::weak_ptr<LuaScript> lua_;
	LuaManager* luaManager_ = nullptr;

public:

	DummyParticle() = default;
	~DummyParticle() = default;

	void Init()
	{
		sEmit_ = std::make_unique<Emitter::SphereEmitter>();
		sEmit_->Create();

		cField_ = std::make_unique<GpuField::ConstantField>();
		cField_->Create(sEmit_->GetWeak_Particle());

		luaManager_ = LuaManager::GetInstance();
		luaManager_->LoadScript("LuaScript", "Test.lua");
		lua_ = luaManager_->GetScript("Test");
		
		sEmit_->Load_EmitData_From_Lua(lua_);
		sEmit_->Load_EmitRangeData_From_Lua(lua_);
		sEmit_->Load_EmitConfigData_From_Lua(lua_);
		cField_->Load_FieldData_From_Lua(lua_);
	}

	void Update()
	{
		sEmit_->Update();
		cField_->Update();
	}

	void Draw()
	{
		sEmit_->Draw3D();
	}

private:

};
