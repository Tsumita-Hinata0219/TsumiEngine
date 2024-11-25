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
	// IParticle
	for (auto& element : particleList_) {
		element->Update();
	}
	// 死亡フラグが立っていたら削除
	particleList_.remove_if([](std::shared_ptr<IPlayerParticle> particle) {
		if (particle->IsDead()) {
			return true;
		}
		return false;
		}
	);

#ifdef _DEBUG
	DrawImGui();
#endif // _DEBUG
}


/// <summary>
/// 描画処理
/// </summary>
void PlayerParticleManager::Draw()
{
	// IParticle
	for (auto& element : particleList_) {
		element->Draw3D();
	}
}


/// <summary>
/// 移動パーティクルの追加
/// </summary>
void PlayerParticleManager::AddMovementPartiucle()
{
	// 追加するインスタンス
	std::shared_ptr<PlayerMovementParticle> newParticle =
		std::make_unique<PlayerMovementParticle>();

	newParticle->Init(); // 初期化
	Scope scope = { -1.0f, 1.0f };
	Vector3 diff = {
		RandomGenerator::getRandom(scope),
		RandomGenerator::getRandom(scope),
		RandomGenerator::getRandom(scope),
	};
	newParticle->SetTranslate(player_->GetWorldPos() + diff);
	newParticle->SetRotate(diff);

	this->particleList_.push_back(std::move(newParticle));
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
