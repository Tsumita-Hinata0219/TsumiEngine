#include "StageTransitionMenuNaviBack.h"



/// <summary>
/// 初期化処理
/// </summary>
void StageTransitionMenuNaviBack::Init()
{
	// 入力
	input_ = Input::GetInstance();

	// テクスチャ
	uint32_t backTexHD = TextureManager::LoadTexture(
		"Texture/Game/StageTransitionMenu", "StageTransitionMenu_BackScreen.png");
	uint32_t frameTexHD = TextureManager::LoadTexture(
		"Texture/Game/StageTransitionMenu",	"StageTransitionMenu_Frame.png");
	texHDArr_ = { backTexHD, frameTexHD };

	// スプライトサイズ
	Vector2 spriteSize = { 192.0f, 36.0f };
	sizeArr_ = { spriteSize, spriteSize };

	for (int i = 0; i < arraySize_; ++i) {

		// スプライト
		spriteArr_[i] = std::make_unique<Sprite>();
		spriteArr_[i]->Initn(spriteSize);
		spriteArr_[i]->SetAnchor(SpriteAnchor::Center);
		spriteArr_[i]->SetTexture(texHDArr_[i]);
		spriteArr_[i]->SetColor(Samp::Color::WHITE);

		// トランスフォーム
		transArr_[i].Init();
	}

	// 選択しているものはNoneにしておく
	nowSelect_ = MenuSelect::Other;
}


/// <summary>
/// 更新処理
/// </summary>
void StageTransitionMenuNaviBack::Update()
{
	// セレクト操作
	SelectOperation();

#ifdef _DEBUG
	// ImGuiの描画
	DrawImGui();
#endif // _DEBUG
}


/// <summary>
/// 描画処理
/// </summary>
void StageTransitionMenuNaviBack::Draw2DFront()
{
	for (int i = 0; i < arraySize_; ++i) {
		spriteArr_[i]->SetSize(sizeArr_[i]);
		spriteArr_[i]->Draw(transArr_[i]);
	}
}


/// <summary>
/// セレクト操作
/// </summary>
void StageTransitionMenuNaviBack::SelectOperation()
{
	// LStickの入力を取得
	iLStick_ = input_->GetLStick();

	// 左入力
	if (iLStick_.x < -DZone_ || input_->Trigger(PadData::LEFT) || 
		input_->Trigger(DIK_LEFT) || input_->Trigger(DIK_A)) {
		ChangeSelect(MenuSelect::Back);
	}
	else if (iLStick_.x > DZone_ || input_->Trigger(PadData::RIGHT) || 
		input_->Trigger(DIK_RIGHT) || input_->Trigger(DIK_D)) {
		ChangeSelect(MenuSelect::Next);
	}
}


/// <summary>
/// セレクト変更
/// </summary>
void StageTransitionMenuNaviBack::ChangeSelect(MenuSelect select)
{
	if (nowSelect_ != select) {

		// 選択中を更新
		nowSelect_ = select;

		// 座標を更新
		for (auto& element : transArr_) {
			element.srt.translate = targetPos_[int(nowSelect_)];
		}
	}
}


/// <summary>
/// ImGuiの描画
/// </summary>
void StageTransitionMenuNaviBack::DrawImGui()
{
	if (ImGui::TreeNode("StageTransitionMenu_NaviBack")) {

		if (nowSelect_ == MenuSelect::Other) {
			ImGui::Text("NowSelect : Other");
		}
		else if (nowSelect_ == MenuSelect::Back) {
			ImGui::Text("NowSelect : Back");
		}
		else if (nowSelect_ == MenuSelect::Next) {
			ImGui::Text("NowSelect : Next");
		}
		ImGui::Text("");

		ImGui::Text("Input");
		ImGui::DragFloat2("L_Stick", &iLStick_.x, 0.0f);
		ImGui::Text("");

		ImGui::TreePop();
	}
}
