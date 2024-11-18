#include "StageTransitionMenuNaviBack.h"



/// <summary>
/// 初期化処理
/// </summary>
void StageTransitionMenuNaviBack::Init()
{
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
		spriteArr_[i]->SetColor(Samp::Color::BLACK);

		// トランスフォーム
		transArr_[i].Init();
	}

	// 選択しているものはNoneにしておく
	nowSelect_ = MenuNowSelect::Back;
}


/// <summary>
/// 更新処理
/// </summary>
void StageTransitionMenuNaviBack::Update()
{
	/*if (nowSelect_ == MenuNowSelect::Back) {
		for (auto& element : transArr_) {
			element.srt.translate = targetPos_[int(MenuNowSelect::Back)];
		}
	}
	else if (nowSelect_ == MenuNowSelect::Back) {
		for (auto& element : transArr_) {
			element.srt.translate = targetPos_[int(MenuNowSelect::Next)];
		}
	}*/

	for (auto& element : transArr_) {
		element.srt.translate = targetPos_[int(nowSelect_)];
	}

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
/// ImGuiの描画
/// </summary>
void StageTransitionMenuNaviBack::DrawImGui()
{
	if (ImGui::TreeNode("StageTransitionMenu_NaviBack")) {

		if (nowSelect_ == MenuNowSelect::None) {
			ImGui::Text("NowSelect : None");
		}
		else if (nowSelect_ == MenuNowSelect::Back) {
			ImGui::Text("NowSelect : Back");
		}
		else if (nowSelect_ == MenuNowSelect::Next) {
			ImGui::Text("NowSelect : Next");
		}

		ImGui::TreePop();
	}
}
