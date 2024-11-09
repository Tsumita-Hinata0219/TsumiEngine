#include "TitleScreen.h"
#include "Base/WinApp/WinApp.h"


// 初期化処理
void TitleScreen::Init()
{
	// Inputクラス
	input_ = Input::GetInstance();
	
	/* ----- Screen スクリーン ----- */
	// Modelの読み込みと設定
	modelManager_ = ModelManager::GetInstance();
	modelManager_->LoadModel("Obj/TitleScreen", "TitleScreenobj.obj");
	screenModel_ = modelManager_->GetModel("TitleScreenobj");
	// Transformの初期化
	screenTrans_.Init();
	screenTrans_.srt.translate.z = 5.0f;
	pTrans_.Init();
	pTrans_.srt.scale = { 0.2f, 0.2f, 0.2f };
	pTrans_.srt.translate.z = 4.5f;
	// Parentを組む
	screenTrans_.SetParent(&pTrans_);


	/* ----- Cursor カーソル ----- */
	// Spriteの読み込みと設定
	cursorTexHD_ = TextureManager::LoadTexture("Texture", "8.png");
	cursorSprite_ = std::make_unique<Sprite>();
	cursorSprite_->Init({ 64.0f, 64.0f });
	cursorSprite_->SetAnchor(SpriteAnchor::Center);
	cursorSprite_->SetColor(Samp::Color::YELLOW);
	// Transfromの初期化
	cursorTrans_.Initialize();
	cursorTrans_.srt.translate = { WinApp::kHalfWindowWidth, WinApp::kHalfWindowHeight, 0.0f };
	// カーソルの移動速度
	cursorSpeed_ = 15.0f;


	// RangeInputとOutputの設定
	rangeInput_ = {
		{ 0.0f, WinApp::kWindowWidth },
		{ 0.0f, WinApp::kWindowHeight },
	};
	rangeOutput_ = { -1.0f, +1.0f };
}


// 更新処理
void TitleScreen::Update()
{
	// Transformの更新処理
	cursorTrans_.UpdateMatrix();
	pTrans_.UpdateMatrix();

	// カーソルの移動処理
	CurSorMove();

	// 加算姿勢の計算
	CalcAddRotate();

	// スクリーンの姿勢計算
	CalcScreenRotate();

#ifdef _DEBUG
	
	if (ImGui::TreeNode("TitleScreen")) {

		ImGui::Text("");
		screenTrans_.DrawImGui("screen");

		ImGui::Text("");
		pTrans_.DrawImGui("test");

		ImGui::Text("");
		ImGui::DragFloat("CurSor_Speed", &cursorSpeed_, 0.01f);


		ImGui::Text("");
		ImGui::DragFloat3("spritePos", &cursorTrans_.srt.translate.x, 0.01f);

		ImGui::Text("");
		ImGui::DragFloat2("addRotate", &addRotate_.x, 0.01f);

		ImGui::TreePop();
	}
#endif // _DEBUG
}


// 描画処理
void TitleScreen::Draw3D()
{
	screenModel_->DrawN(screenTrans_);
}
void TitleScreen::Draw2DFront() 
{
	cursorSprite_->Draw(cursorTexHD_, cursorTrans_);
}
void TitleScreen::Draw2DBack() {}


// 衝突判定コールバック関数
void TitleScreen::onCollision([[maybe_unused]] IObject* object, [[maybe_unused]] Col::ColData colData)
{
}


// カーソルの移動処理
void TitleScreen::CurSorMove()
{
	// velocityは0で毎フレーム初期化
	velocity_ = Vector3::zero;

	// キーの処理
	KeyMove();

	// パッドの処理
	PadMove();
}
void TitleScreen::KeyMove()
{
	// キーの処理
	if (input_->Press(DIK_W)) {};
	if (input_->Press(DIK_A)) {};
	if (input_->Press(DIK_S)) {};
	if (input_->Press(DIK_D)) {};
}
void TitleScreen::PadMove()
{
	// stickの入力を受け取る
	L_StickInput_ = input_->GetLStick();

	// stick入力が一定範囲を超えている場合更新
	if (std::abs(L_StickInput_.x) > 0.2f || std::abs(L_StickInput_.y) > 0.2f) {

		// 移動量
		velocity_ = {
			L_StickInput_.x,
			L_StickInput_.y,
			0.0f,
		};

		// 移動量に速さを反映
		velocity_ = Normalize(velocity_) * cursorSpeed_;

		// SpriteなのでY軸反転
		velocity_.y *= -1.0f;

		// 移動
		cursorTrans_.srt.translate += velocity_;

		// 移動限界
		cursorTrans_.srt.translate.x = max(cursorTrans_.srt.translate.x, 0.0f);
		cursorTrans_.srt.translate.x = min(cursorTrans_.srt.translate.x, float(WinApp::kWindowWidth));
		cursorTrans_.srt.translate.y = max(cursorTrans_.srt.translate.y, 0.0f);
		cursorTrans_.srt.translate.y = min(cursorTrans_.srt.translate.y, float(WinApp::kWindowHeight));
	}
}


// 加算姿勢の計算
void TitleScreen::CalcAddRotate()
{
	addRotate_ = {
		ConvertToRange(rangeInput_.second, rangeOutput_, cursorTrans_.srt.translate.y),
		ConvertToRange(rangeInput_.first, rangeOutput_, cursorTrans_.srt.translate.x),
	};

	addRotate_ /= 10.0f;
}


// スクリーンの姿勢計算
void TitleScreen::CalcScreenRotate()
{
	// スクリーンと親子関係を結んでいる親の姿勢を変更する
	pTrans_.srt.rotate.x = (-addRotate_.x);
	pTrans_.srt.rotate.y = (-addRotate_.y);
}
