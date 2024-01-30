#include "FadeManager.h"



// 初期化処理
void FadeManager::Initialize()
{
	// テクスチャの読み込み
	FadeManager::GetInstance()->texHD_ = TextureManager::LoadTexture("Fade.png");

	// スプライトの初期化
	FadeManager::GetInstance()->sprite_ = make_unique<Sprite>();
	FadeManager::GetInstance()->sprite_->Initialize(Vector2::zero, WinApp::WindowSize());

	// スプライトトランスフォームの初期化
	FadeManager::GetInstance()->st_.Initialize();

	// カラーの設定
	FadeManager::GetInstance()->color_ = Vector4::oneW;
}


// 描画処理
void FadeManager::Draw(ViewProjection view)
{
	// カラーの設定
	FadeManager::GetInstance()->sprite_->SetColor(FadeManager::GetInstance()->color_);

	uint32_t texHandle = FadeManager::GetInstance()->texHD_;
	SpriteTransform spriteTransform = FadeManager::GetInstance()->st_;
	FadeManager::GetInstance()->sprite_->Draw(texHandle, spriteTransform, view);


#ifdef _DEBUG

	if (ImGui::TreeNode("Fade"))
	{
		ImGui::ColorEdit4("Color", &FadeManager::GetInstance()->color_.x);
		ImGui::TreePop();
	}

#endif // _DEBUG
}


//フェードイン処理
bool FadeManager::IsFadeIn()
{
	// すでに画面が真っ暗の状態なら早期リターン
	if (FadeManager::GetInstance()->state_.isFadeIn && 
		!FadeManager::GetInstance()->state_.isFadeOut) {
		return false;
	}

	// フレームなどの変数初期化
	FadeManager::FrameInit();

	// 補間の計算
	FadeManager::FrameUpdate(func_FadeIn);

	// 補間が終了したら、ステートの設定して、trueを返す
	if (FadeManager::GetInstance()->time_ >= 1.0f) {
		FadeManager::GetInstance()->state_.isFadeIn = true;
		FadeManager::GetInstance()->state_.isFadeOut = false;

		return true;
	}

	return false;
}


// フェードアウト処理
bool FadeManager::IsFadeOut()
{
	// すでに画面が開けた状態なら早期リターン
	if (FadeManager::GetInstance()->state_.isFadeOut) {
		return false;
	}

	// フレームなどの変数初期化
	FadeManager::FrameInit();

	// 補間の計算
	FadeManager::FrameUpdate(func_FadeOut);

	// 補間が終了したら、ステートの設定して、trueを返す
	if (FadeManager::GetInstance()->time_ >= 1.0f) {
		FadeManager::GetInstance()->state_.isFadeIn = true;
		FadeManager::GetInstance()->state_.isFadeOut = false;

		return true;
	}

	return false;
}


// フレームの初期化
void FadeManager::FrameInit()
{
	FadeManager::GetInstance()->startFrame_ = 0;
	FadeManager::GetInstance()->finishFrame_ = 600;
	FadeManager::GetInstance()->time_ = 0.0f;
}


// フレームの更新処理
void FadeManager::FrameUpdate(FunctionFade func)
{
	// フレームの加算
	FadeManager::GetInstance()->startFrame_++;

	// 補間割合の計算
	FadeManager::GetInstance()->time_ = 
		float(FadeManager::GetInstance()->startFrame_ / FadeManager::GetInstance()->finishFrame_);

	// 補間の処理
	if (func == func_FadeIn) {

		FadeManager::GetInstance()->color_.w =
			Lerp(
				float(0.0f),
				float(1.0f),
				FadeManager::GetInstance()->time_);
	}
	else if (func == func_FadeOut) {

		FadeManager::GetInstance()->color_.w =
			Lerp(
				float(1.0f),
				float(0.0f),
				FadeManager::GetInstance()->time_);
	}

	// カラーの設定
	FadeManager::GetInstance()->sprite_->SetColor(FadeManager::GetInstance()->color_);
}
