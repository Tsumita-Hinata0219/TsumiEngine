#include "DummyParticle.h"
#include "3D/Model/Manager/ModelManager.h"


DummyParticle::DummyParticle()
{
	sEmit_ = std::make_unique<Emitter::SphereEmitter>();
	cField_ = std::make_unique<GpuField::ConstantField>();
	modelManager_ = ModelManager::GetInstance();
}

void DummyParticle::Init()
{
	// Emitter生成
	sEmit_->Create("Obj/Dev/Test", "Test.obj");
	// ParticleField生成
	cField_->Create(sEmit_->GetWeak_Particle());

	// Luaの読み込み & 取得
	auto luaManager = LuaManager::GetInstance();
	luaManager->LoadScript("LuaScript/Dummy", "DummyParticle_Params.lua");
	particlePropeLua_ = luaManager->GetScript("DummyParticle_Params");
	luaManager->LoadScript("LuaScript/Dummy", "Dummy_Movement.lua");
	movementLua_ = luaManager->GetScript("Dummy_Movement");

	// Luaから値を受け取る
	sEmit_->Load_EmitData_From_Lua(particlePropeLua_);
	sEmit_->Load_EmitRangeData_From_Lua(particlePropeLua_);
	sEmit_->Load_EmitConfigData_From_Lua(particlePropeLua_);
	cField_->Load_FieldData_From_Lua(particlePropeLua_);
	particlePropeLua_.lock()->SetReloadCallback([this]() { ReLoad_ParticlePrope(); });

	// 確認用Emitterの描画用
	modelManager_->LoadModel("Obj/Emitter/Sphere", "SphereEmitter.obj");
	model_ = modelManager_->GetModel("SphereEmitter");
	model_->SetRenderState(RenderState::FillMode_WireFrame);
	trans_.Init();
}

void DummyParticle::Update()
{
	// Emitterの座標を動かす処理
	if (auto lockedData = sEmit_->GetWeak_EmitData().lock()) {

		Vector4 vel = { 0.0f, 0.0f, 0.01f, 0.0f };
		// Lua側の関数でEmitterを動かす
		if (movementLua_.lock()->ExeFunction("MoveCircular", vel)) {
			lockedData->translate = movementLua_.lock()->GetVariable<Vector4>("position");
		}

		// 確認用Emitterの座標更新
		trans_.srt.translate = {
			lockedData->translate.x,
			lockedData->translate.y,
			lockedData->translate.z,
		};
	}

	// EmitterとFieldの更新
	sEmit_->Update();
	sEmit_->TimerUpdate();
	cField_->Update();

	trans_.DrawImGui();
}

void DummyParticle::Draw()
{
	sEmit_->Draw3D();
	model_->Draw(trans_);
}

void DummyParticle::ReLoad_ParticlePrope()
{
	sEmit_->Load_EmitData_From_Lua(particlePropeLua_);
	sEmit_->Load_EmitRangeData_From_Lua(particlePropeLua_);
	sEmit_->Load_EmitConfigData_From_Lua(particlePropeLua_);
	cField_->Load_FieldData_From_Lua(particlePropeLua_);
}
