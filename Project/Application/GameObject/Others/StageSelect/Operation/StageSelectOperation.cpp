#include "StageSelectOperation.h"



/// <summary>
/// 初期化処理
/// </summary>
void StageSelectOperation::Init()
{
	// Inputのインスタンス取得
	input_ = Input::GetInstance();

	// ステージのセレクト番号
	selectNum_ = 0;
}


/// <summary>
/// 更新処理
/// </summary>
void StageSelectOperation::Update()
{





#ifdef _DEBUG
	DrawImGui();
#endif // _DEBUG
}


/// <summary>
/// セレクトの操作
/// </summary>
void StageSelectOperation::SelectOperation()
{
	//// 左入力
	//if (iLStick_.x < -DZone_ || input_->Trigger(PadData::LEFT) ||
	//	input_->Trigger(DIK_LEFT) || input_->Trigger(DIK_A)) {
	//	ChangeSelect(MenuSelect::Back);
	//}
	//// 右入力
	//if (iLStick_.x > DZone_ || input_->Trigger(PadData::RIGHT) ||
	//	input_->Trigger(DIK_RIGHT) || input_->Trigger(DIK_D)) {
	//	ChangeSelect(MenuSelect::Next);
	//}
}


/// <summary>
/// DrawImGuiの描画
/// </summary>
void StageSelectOperation::DrawImGui()
{
	if (ImGui::TreeNode("SelectOperation")) {

		ImGui::DragInt("Select_Number", &selectNum_, 0);
		ImGui::Text("");

		ImGui::TreePop();
	}
}

