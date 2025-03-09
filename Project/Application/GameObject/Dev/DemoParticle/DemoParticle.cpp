#include "DemoParticle.h"


/// <summary>
/// 初期化処理
/// </summary>
void DemoParticle::Init()
{
	// Particle生成
	particle_ = std::make_shared<GPUParticle>();
	particle_->Init();

	// Emitter生成
	emitter_ = std::make_unique<GPUParticleEmitter<GpuEmitter::SphereEmitter>>();
	emitter_->Create(particle_);

	// Emit Dataを取得
	emitData_ = emitter_->GetEmitData();
	emitData_.lock()->translate = Vector3::one;
	emitData_.lock()->radius = 1.0f;

	// Emit Configを取得
	emitConfig_ = emitter_->GetEmitConfig();
	emitConfig_.lock()->spawnInterval = 0.5f;
	emitConfig_.lock()->elapsedTime = emitConfig_.lock()->spawnInterval;
	emitConfig_.lock()->spawnCount = 5;
	emitConfig_.lock()->isEmitting = 0;

	// Emit Rangeを取得
	emitRange_ = emitter_->GetEmitRange();
	emitRange_.lock()->scaleMin = { 0.2f, 0.2f, 0.2f, 0.0f };
	emitRange_.lock()->scaleMax = { 0.6f, 0.6f, 0.6f, 0.0f };
	emitRange_.lock()->rotateMin = { 0.0f, 0.0f, 0.0f, 0.0f };
	emitRange_.lock()->rotateMax = { 0.0f, 0.0f, 0.0f, 0.0f };
	emitRange_.lock()->translateMin = { -2.0f, -2.0f, -2.0f, 0.0f };
	emitRange_.lock()->translateMax = { 2.0f, 2.0f, 2.0f, 0.0f };
	emitRange_.lock()->colorMin = { 0.0f, 0.0f, 0.0f, 1.0f };
	emitRange_.lock()->colorMax = { 1.0f, 1.0f, 1.0f, 1.0f };
	emitRange_.lock()->velocityMin = { 0.0f, 0.0f, 0.0f, 0.0f };
	emitRange_.lock()->velocityMax = { 0.0f, 0.0f, 0.0f, 0.0f };
	emitRange_.lock()->baseLifeTime = 1.0f * 60.0f;
	emitRange_.lock()->lifeTimeMin = 0;
	emitRange_.lock()->lifeTimeMax = 0;

	// Field生成
	field_ = std::unique_ptr<GPUParticleField<GpuField::ConstantField>>();
	field_->Create(particle_);

	// Field Dataの取得
	fieldData_ = field_->GetFieldData();

}


/// <summary>
/// 更新処理
/// </summary>
void DemoParticle::Update()
{
	// エミッター更新処理
	emitter_->Update();
	emitter_->Emit();

	// パーティクル更新
	particle_->Update();

#ifdef _DEBUG
	DrawImGui();
#endif // _DEBUG
}


/// <summary>
/// 描画処理
/// </summary>
void DemoParticle::Draw()
{
	particle_->Draw();
}


/// <summary>
/// ImGui描画
/// </summary>
void DemoParticle::DrawImGui()
{
	if (ImGui::TreeNode("Demo Particle")) {

		if(ImGui::Button("Emit")) {
			emitter_->Emit();
		}
		ImGui::Text("");

		auto time = emitConfig_.lock()->elapsedTime;
		ImGui::Text("Emit Time : %.2f", float(time));
		ImGui::Text("");


		ImGui::TreePop();
	}
}

