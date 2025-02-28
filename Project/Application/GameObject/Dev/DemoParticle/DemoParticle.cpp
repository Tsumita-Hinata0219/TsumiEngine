#include "DemoParticle.h"


/// <summary>
/// 初期化処理
/// </summary>
void DemoParticle::Init()
{
	// パーティクル作成
	particle_ = std::make_shared<GPUParticle>();
	particle_->Init();

	// エミッター作成
	emitter_ = std::make_unique<GPUParticleEmitter<GpuParticle::SphereEmitter>>();
	emitter_->Create(particle_);
	// エミッターのデータを取得
	emitData_ = emitter_->GetEmitData();
	emitData_.lock()->translate = Vector3::one;
	emitData_.lock()->radius = 1.0f;
	// エミッターコンフィグを取得
	emitConfig_ = emitter_->GetEmitConfig();
	emitConfig_.lock()->spawnInterval = 1.0f;
	emitConfig_.lock()->elapsedTime = 0.0f;
	emitConfig_.lock()->isEmitting = 0;
}


/// <summary>
/// 更新処理
/// </summary>
void DemoParticle::Update()
{
	//emitter_->Emit();
	emitter_->Update();
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
	/* ----- DemoParticle デモパーティクル ----- */
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

		ImGui::TreePop();
	}
}
