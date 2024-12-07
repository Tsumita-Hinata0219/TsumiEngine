#include "StageSelectOperation.h"
#include "../Manager/StageSelectManager.h"


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
	// LStickの入力を取得
	iLStick_ = input_->GetLStick();

	// フラグが立っているとき
	if (isOperationFunc_) {

		// stickを戻したらフラグを折る
		if (iLStick_.x >= -DZone_ && iLStick_.x <= DZone_) {
			isOperationFunc_ = false;
		}
	}

	// セレクト操作
	SelectOperation();



#ifdef _DEBUG
	DrawImGui();
#endif // _DEBUG
}


/// <summary>
/// セレクトの操作
/// </summary>
void StageSelectOperation::SelectOperation()
{
	// 操作が行われたら通らない
	if (isOperationFunc_) { return; }

	// 左入力
	if (iLStick_.x < -DZone_ || input_->Trigger(PadData::LEFT) ||
		input_->Trigger(DIK_LEFT) || input_->Trigger(DIK_A)) {
		ChangeSelect(SelectionDirection::Previous);
	}
	// 右入力
	if (iLStick_.x > DZone_ || input_->Trigger(PadData::RIGHT) ||
		input_->Trigger(DIK_RIGHT) || input_->Trigger(DIK_D)) {
		ChangeSelect(SelectionDirection::Next);
	}
}


/// <summary>
/// セレクトチェンジ
/// </summary>
void StageSelectOperation::ChangeSelect(SelectionDirection dir)
{
	// 操作フラグを立てる
	isOperationFunc_ = true;

	if (dir == SelectionDirection::Previous) {
		if (selectNum_ <= 0) {
			return;
		}
		// デクリメント
		selectNum_--;
	}
	else if (dir == SelectionDirection::Next) {
		if (selectNum_ >= StageSelectManager::kMaxStage) {
			return;
		}
		// インクリメント
		selectNum_++;
	}
}


/// <summary>
/// DrawImGuiの描画
/// </summary>
void StageSelectOperation::DrawImGui()
{
	if (ImGui::TreeNode("SelectOperation")) {

		ImGui::DragInt("Select_Number", &selectNum_, 0);
		ImGui::Text("");

		ImGui::Checkbox("Operation_Func", &isOperationFunc_);
		ImGui::Text("");

		ImGui::TreePop();
	}
}

