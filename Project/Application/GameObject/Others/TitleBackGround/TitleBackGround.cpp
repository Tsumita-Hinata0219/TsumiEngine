#include "TitleBackGround.h"



// 初期化処理
void TitleBackGround::Init()
{
	// 配列のresize
	back_.resize(EnumSize<TitleSceneBGType>::value);

	// スプライトとトランスフォームの初期化と設定
	for (auto& element : back_) {
		element.sprite = std::make_unique<Sprite>();
		element.sprite->Init();
		element.transfrom.Initialize();

		// オリジンの設定
		element.sprite->SetAnchor(SpriteAnchor::Center);
		// サイズの設定
		element.sprite->SetSize(WinApp::WindowSize());
		// 座標の設定
		element.transfrom.srt.translate = { WinApp::kHalfWindowWidth, WinApp::kHalfWindowHeight, 0.0f };
	}
	
	// テクスチャの読み込み　
	back_[enum_val(TitleSceneBGType::Monochromatic)].texture =
		TextureManager::LoadTexture("Texture/Title", "TitleBackGround.png");
	back_[enum_val(TitleSceneBGType::Vignetting)].texture =
		TextureManager::LoadTexture("Texture/Title", "TitleVignetting.png");
}


// 更新処理
void TitleBackGround::Update()
{
	// トランスフォームの更新
	for (auto& element : back_) {
		element.transfrom.UpdateMatrix();
	}
}


// 描画処理
void TitleBackGround::Draw2DBack()
{
	back_[enum_val(TitleSceneBGType::Monochromatic)].sprite->Draw(
		back_[enum_val(TitleSceneBGType::Monochromatic)].texture, 
		back_[enum_val(TitleSceneBGType::Monochromatic)].transfrom);
}

void TitleBackGround::Draw2DFront()
{
	back_[enum_val(TitleSceneBGType::Vignetting)].sprite->Draw(
		back_[enum_val(TitleSceneBGType::Vignetting)].texture,
		back_[enum_val(TitleSceneBGType::Vignetting)].transfrom);
}
