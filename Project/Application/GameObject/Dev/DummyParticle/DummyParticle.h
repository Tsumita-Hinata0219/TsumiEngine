#pragma once

#include "GameObject/GameObject.h"



class DummyParticle
{
private:
	std::unique_ptr<Emitter::SphereEmitter> sEmit_;
	std::weak_ptr<Emitter::Data::SphereEmit> sEmitData_;

	std::unique_ptr<GpuField::ConstantField> cField_;
	std::weak_ptr<LuaScript> lua_;
	LuaManager* luaManager_ = nullptr;

	std::unique_ptr<Model> model_;
	ModelManager* modelManager_ = nullptr;
	Transform trans_{};

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

		modelManager_ = ModelManager::GetInstance();
		modelManager_->LoadModel("Obj/Emitter/Sphere", "SphereEmitter.obj");
		model_ = modelManager_->GetModel("SphereEmitter");
		model_->SetRenderState(RenderState::FillMode_WireFrame);

		trans_.Init();
	}

	void Update()
	{
		sEmit_->Update();
		cField_->Update();

		if (auto lockedData = sEmit_->GetWeak_EmitData().lock()) {

			Vector4 vel = { 0.0f, 0.0f, 0.1f, 0.0f };
			if (lua_.lock()->ExeFunction("Move", vel)) {
				lockedData->translate = lua_.lock()->GetVariable<Vector4>("position");
			}

			trans_.srt.translate = {
				lockedData->translate.x,
				lockedData->translate.y,
				lockedData->translate.z,
			};
		}
	}

	void Draw()
	{
		sEmit_->Draw3D();
		model_->Draw(trans_);
	}

private:

};
