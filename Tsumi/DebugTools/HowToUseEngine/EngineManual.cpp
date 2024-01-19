#include "EngineManual.h"



/// <summary>
/// デストラクタ
/// </summary>
EngineManual::~EngineManual() {

	Audio::SoundUnload();
}


/// <summary>
/// 初期化処理
/// </summary>
void EngineManual::Initialize() {

	// テクスチャの読み込み
	uvCheckerHD_ = TextureManager::LoadTexture("uvChecker.png");
	monsterBallHD_ = TextureManager::LoadTexture("monsterBall.png");
	asanohaHD_ = TextureManager::LoadTexture("asanoha.png");
	skyHD_ = TextureManager::LoadTexture("sky.png");


	// サウンドの読み込み
	mokugyoHD_ = Audio::LoadSound("mokugyo.wav");
	kakkoiiHD_ = Audio::LoadSound("kakkoii.wav");

	//Audio::PlayOnSound(kakkoiiHD_, true, 1.0f);


	// スプライト
	spriteFront_ = make_unique<Sprite>();
	spriteFront_->Initialize({ 0.0f, 0.0f }, { 400.0f, 300.0f });
	spriteFrontTrans_.Initialize();

	spriteBack_ = make_unique<Sprite>();
	spriteBack_->Initialize({ 0.0f, 0.0f }, { 600.0f, 500.0f });
	spriteBackTrans_.Initialize();

	// Obj
	modelObj_ = make_unique<Model>();
	modelObj_->CreateFromObj("axis");
	modelTrans_.Initialize();

}


/// <summary>
/// 更新処理
/// </summary>
void EngineManual::Update() {

	AudioUpdate();

	
	spriteFrontTrans_.UpdateMatrix();
	spriteBackTrans_.UpdateMatrix();
	modelTrans_.UpdateMatrix();

#ifdef _DEBUG

	ImGui::Begin("EngineManual");
	ImGui::Text("SpriteFront");
	ImGui::DragFloat3("SpriteF_Scale", &spriteFrontTrans_.scale.x, 0.01f);
	ImGui::DragFloat3("SpriteF_Rotate", &spriteFrontTrans_.rotate.x, 0.01f);
	ImGui::DragFloat3("SpriteF_Translate", &spriteFrontTrans_.translate.x, 0.01f);
	ImGui::Text("SpriteBack");
	ImGui::DragFloat3("SpriteB_Scale", &spriteBackTrans_.scale.x, 0.01f);
	ImGui::DragFloat3("SpriteB_Rotate", &spriteBackTrans_.rotate.x, 0.01f);
	ImGui::DragFloat3("SpriteB_Translate", &spriteBackTrans_.translate.x, 0.01f);
	ImGui::Text("Axis");
	ImGui::DragFloat3("Axis_Scale", &modelTrans_.scale.x, 0.01f);
	ImGui::DragFloat3("Axis_Rotate", &modelTrans_.rotate.x, 0.01f);
	ImGui::DragFloat3("Axis_Translate", &modelTrans_.translate.x, 0.01f);
	ImGui::End();

#endif // _DEBUG

}


/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void EngineManual::BackSpriteDraw(ViewProjection view) {

	spriteBack_->Draw(asanohaHD_, spriteBackTrans_, view);
}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void EngineManual::ModelDraw(ViewProjection view) {

	modelObj_->Draw(modelTrans_, view);
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void EngineManual::FrontSpriteDraw(ViewProjection view) {

	spriteFront_->Draw(monsterBallHD_, spriteFrontTrans_, view);
}


/// <summary>
/// Audioに関する処理まとめたやつ
/// </summary>
void EngineManual::AudioUpdate() {

	//if (KeyInput::PressKeys(DIK_B)) {

	//	if (KeyInput::TriggerKey(DIK_1)) {
	//		Audio::PlayOnSound(mokugyoHD_, true, 1.0f);
	//	}

	//	if (KeyInput::TriggerKey(DIK_2)) {
	//		Audio::PlayOnSound(mokugyoHD_, false, 1.0f);
	//	}

	//	if (KeyInput::TriggerKey(DIK_3)) {
	//		Audio::PlayOnSound(kakkoiiHD_, false, 1.0f);
	//	}
	//}
	//if (KeyInput::PressKeys(DIK_S)) {

	//	if (KeyInput::TriggerKey(DIK_1)) {
	//		Audio::StopOnSound(mokugyoHD_);
	//	}

	//	if (KeyInput::TriggerKey(DIK_2)) {
	//		Audio::StopOnSound(kakkoiiHD_);
	//	}
	//}


#ifdef _DEBUG


	ImGui::Begin("Audio");

	ImGui::Text("mokugyo : B + 1 -> Loop");
	ImGui::Text("          B + 2 -> nonLoop");
	if (Audio::IsPlaying(mokugyoHD_)) {
		ImGui::Text("mokugyo_isPlaying : true");
	}
	else {
		ImGui::Text("mokugyo_isPlaying : false");
	}

	ImGui::Text("\nkakkoii : B + 3 -> nonLoop");
	if (Audio::IsPlaying(kakkoiiHD_)) {
		ImGui::Text("nkakkoii_isPlaying : true");
	}
	else {
		ImGui::Text("nkakkoii_isPlaying : false");
	}
	ImGui::End();

#endif // _DEBUG
}