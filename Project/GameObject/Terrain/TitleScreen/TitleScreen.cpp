#include "TitleScreen.h"
#include "../../Tsumi/Base/WinApp/WinApp.h"


// 初期化処理
void TitleScreen::Init()
{
	/* ----- Screen スクリーン ----- */
	// Modelの読み込みと設定
	modelManager_ = ModelManager::GetInstance();
	modelManager_->LoadModel("Obj/TitleScreen", "TitleScreenobj.obj");
	screenModel_ = modelManager_->GetModel("TitleScreenobj");
	// Transformの初期化
	trans_.Init();
	trans_.srt.translate.z = 5.0f;


	/* ----- Cursor カーソル ----- */
	// Spriteの読み込みと設定
	cursorTexHD_ = TextureManager::LoadTexture("Texture", "8.png");
	cursorSprite_ = std::make_unique<Sprite>();
	cursorSprite_->Init({ 64.0f, 64.0f });
	// Transfromの初期化
	cursorTrans_.Initialize();
	cursorTrans_.srt.translate = { WinApp::kHalfWindowWidth, WinApp::kHalfWindowHeight, 0.0f };


	// Test
	modelManager_->LoadModel("Obj/Test", "Test.obj");
	testModel_ = modelManager_->GetModel("Test");
	ttrans_.Init();
	ttrans_.srt.scale = { 0.2f, 0.2f, 0.2f };
	ttrans_.srt.translate.z = 4.5f;


	// Parentを組む
	trans_.SetParent(&ttrans_);
}


// 更新処理
void TitleScreen::Update()
{
	cursorTrans_.UpdateMatrix();


#ifdef _DEBUG
	
	if (ImGui::TreeNode("TitleScreen")) {

		ImGui::Text("");
		trans_.DrawImGui("screen");

		ImGui::Text("");
		ttrans_.DrawImGui("test");

		ImGui::TreePop();
	}
#endif // _DEBUG
}


// 描画処理
void TitleScreen::Draw3D()
{
	screenModel_->DrawN(trans_);
	testModel_->DrawN(ttrans_);
}
void TitleScreen::Draw2DFront() 
{
	cursorSprite_->Draw(cursorTexHD_, cursorTrans_);
}
void TitleScreen::Draw2DBack() {}
