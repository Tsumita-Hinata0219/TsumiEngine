#include "PlayerParticleManager.h"
#include "../../Player.h"


/// <summary>
/// 初期化処理
/// </summary>
void PlayerParticleManager::Init()
{
}


/// <summary>
/// 更新処理
/// </summary>
void PlayerParticleManager::Update()
{
	// MovementParticle
	for (auto& element : movementParticles_) {
		element->Update();
	}

#ifdef _DEBUG
	DrawImGui();
#endif // _DEBUG
}


/// <summary>
/// 描画処理
/// </summary>
void PlayerParticleManager::Draw()
{
	// MovementParticle
	for (auto& element : movementParticles_) {
		element->Draw3D();
	}
}


/// <summary>
/// 移動パーティクルの追加
/// </summary>
void PlayerParticleManager::AddMovementPartiucle()
{
	// 追加するインスタンス
	std::unique_ptr<PlayerMovementParticle> newParticle =
		std::make_unique<PlayerMovementParticle>();

	newParticle->Init(); // 初期化
	newParticle->SetTranslate(player_->GetWorldPos());

	this->movementParticles_.push_back(std::move(newParticle));
}


/// <summary>
/// ImGuiの描画
/// </summary>
void PlayerParticleManager::DrawImGui()
{
	if (ImGui::TreeNode("PlayerParticleManager")) {

		if (ImGui::Button("Add_MovementParticle")) {
			AddMovementPartiucle();
		}
		ImGui::Text("");


		ImGui::TreePop();
	}
}
