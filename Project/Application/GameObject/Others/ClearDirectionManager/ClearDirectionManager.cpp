#include "ClearDirectionManager.h"



/// <summary>
/// 初期化処理
/// </summary>
void ClearDirectionManager::Init()
{
	input_ = Input::GetInstance();

	/* ----- Direction 演出 ----- */
	directions_.resize(3);
	directions_[0] = std::make_unique<ClearDirectionBackScreen>();
	directions_[1] = std::make_unique<ClearDirectionLiner>();
	directions_[2] = std::make_unique<ClearDirectionMoji>();
	// 各演出の初期化
	for (auto& element : directions_) {
		element->Init();
	}
}


/// <summary>
/// 更新処理
/// </summary>
void ClearDirectionManager::Update()
{
	// 各演出の更新
	for (auto& element : directions_) {
		element->Update();
	}

	if (input_->Trigger(DIK_RETURN)) {
		for (auto& element : directions_) {
			element->StartDirection();
		}
	}
}


/// <summary>
/// 描画処理
/// </summary>
void ClearDirectionManager::Draw2DFront()
{
	// 各演出の描画
	for (auto& element : directions_) {
		element->Draw2DFront();
	}

}


/// <summary>
/// ImGuiの描画
/// </summary>
void ClearDirectionManager::DrawImGui()
{
	if (ImGui::TreeNode("ClearDirection_Manager")) {

		ImGui::Text("Directions_State");
		ShowState("BackScreen", directions_[0]->GetState());
		ShowState("Liner", directions_[1]->GetState());
		ShowState("Moji", directions_[2]->GetState());

		ImGui::Text("");

		ImGui::TreePop();
	}
}


/// <summary>
/// Stateの描画
/// </summary>
void ClearDirectionManager::ShowState(const char* label, ClearDirectionState state)
{
	ImGui::Text("%s_State : ", label); ImGui::SameLine();
	switch (state) {
	case ClearDirectionState::Idle:
		ImGui::Text("Idle");
		break;
	case ClearDirectionState::Processing:
		ImGui::Text("Processing");
		break;
	case ClearDirectionState::Finished:
		ImGui::Text("Finished");
		break;
	}
}

