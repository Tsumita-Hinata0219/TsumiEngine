#include "GameSceneUI.h"



// 初期化処理
void GameSceneUI::Init()
{
	// 配列のresize
	ui_.resize(EnumSize<GameSceneUIType>::value);

	// スプライトとトランスフォームの初期化
	for (int i = 0; i < ui_.size(); ++i) {
		ui_[i].sprite = std::make_unique<Sprite>();
		ui_[i].sprite->Init();
		ui_[i].transfrom.Initialize();
	}

	// テクスチャのサイズ設定


	// 座標の設定


	// テクスチャの読み込み


}


// 更新処理
void GameSceneUI::Update()
{
	// トランスフォームの更新
	for (int i = 0; i < ui_.size(); ++i) {
		ui_[i].transfrom.UpdateMatrix();
	}
}


// 描画処理
void GameSceneUI::Draw2DFront() // 前景
{
	for (int i = 0; i < ui_.size(); ++i) {
		DrawUI(i);
	}
}
void GameSceneUI::Draw2DBack() // 背景
{
}


// UIの描画
void GameSceneUI::DrawUI(int type)
{
	ui_[type].sprite->Draw(ui_[type].texture, ui_[type].transfrom);
}

