#include "ClearDirectionManager.h"



/// <summary>
/// 初期化処理
/// </summary>
void ClearDirectionManager::Init()
{
	input_ = Input::GetInstance();

	/* ----- Direction 演出 ----- */
	directions_.resize(4);
	directions_[0] = std::make_unique<ClearDirectionBlur>();
	directions_[1] = std::make_unique<ClearDirectionBackScreen>();
	directions_[2] = std::make_unique<ClearDirectionLiner>();
	directions_[3] = std::make_unique<ClearDirectionMoji>();
	// 各演出の初期化
	for (auto& element : directions_) {
		element->Init();
	}

	// フラグは折っておく
	isActive_ = false;

	// 初期ステートは待機
	state_ = ClearDirectionState::Idle;
}


/// <summary>
/// 更新処理
/// </summary>
void ClearDirectionManager::Update()
{
#ifdef _DEBUG
	// ImGuiの描画
	DrawImGui();
#endif // _DEBUG

	// ステートが処理中以外なら早期return
	if (state_ != ClearDirectionState::Processing) { return; }

	// 各演出の更新
	for (auto& element : directions_) {
		element->Update();
	}

	// バックスクリーン終わったらその他の演出を始める
	if (directions_[1]->GetState() == ClearDirectionState::Finished) {
		directions_[2]->DirectionStart();
		directions_[3]->DirectionStart();
	}
}


/// <summary>
/// 描画処理
/// </summary>
void ClearDirectionManager::Draw2DFront()
{
	if (!isActive_) { return; }

	// 各演出の描画
	for (auto& element : directions_) {
		element->Draw2DFront();
	}
}


/// <summary>
/// 演出開始
/// </summary>
void ClearDirectionManager::DirectionStart()
{
	if (state_ == ClearDirectionState::Idle) {

		// ステートを処理中へ
		state_ = ClearDirectionState::Processing;

		// フラグを立て
		isActive_ = true;

		// ブラーとバックスクリーンの演出開始
		directions_[0]->DirectionStart();
		directions_[1]->DirectionStart();
	}
}


/// <summary>
/// ImGuiの描画
/// </summary>
void ClearDirectionManager::DrawImGui()
{
	if (ImGui::TreeNode("ClearDirection_Manager")) {

		ImGui::Text("Directions_State");
		ShowState("	BackScreen", directions_[0]->GetState());
		ShowState("	Liner", directions_[1]->GetState());
		ShowState("	Moji", directions_[2]->GetState());

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

