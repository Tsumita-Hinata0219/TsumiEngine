#include "PlayerUI.h"



// 初期化処理
void PlayerUI::Init()
{
	size_t Usize = EnumSize<U>::value;
	Usize;

	// 配列のresize
	ui_.resize(EnumSize<PlayerUIType>::value);

	// スプライトとトランスフォームの初期化
	for (int i = 0; i < ui_.size(); ++i) {
		ui_[i].sprite = std::make_unique<Sprite>();
		ui_[i].sprite->Init();
		ui_[i].transfrom.Initialize();
	}

	// テクスチャのサイズ変更
	ui_[int(PlayerUIType::Shooting)].sprite->SetSize({ 256.0f, 128.0f });

	// テクスチャの読み込み
	ui_[int(PlayerUIType::Shooting)].texture =
		TextureManager::LoadTexture("Texture/Game/Operation_UI", "Player_Shot_UI.png");
}


// 更新処理
void PlayerUI::Update()
{
	// トランスフォームの更新
	for (int i = 0; i < ui_.size(); ++i) {
		ui_[i].transfrom.UpdateMatrix();
	}
}

// 描画処理
void PlayerUI::Draw2DFront() // 前景
{
	// Shooting
	DrawUI(int(PlayerUIType::Shooting));
}
void PlayerUI::Draw2DBack() // 背景
{

}


// UIの描画
void PlayerUI::DrawUI(int type)
{
	ui_[type].sprite->Draw(ui_[type].texture, ui_[type].transfrom);
}
