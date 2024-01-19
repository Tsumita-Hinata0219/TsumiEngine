#include "GameScene.h"



/// <summary>
/// 初期化処理
/// </summary>
void GameScene::Initialize() {

	// メインカメラ
	GameCamera_.Initialize();
	GameCamera_.translate = { 0.0f, 5.0f, -40.0f };


	// スカイドーム
	skydome_ = make_unique<Skydome>();
	skydome_->Initialize();


	// グラウンド
	ground_ = make_unique<Ground>();
	ground_->Initialize();

	// プレイヤー
	player_ = make_unique<Player>();
	player_->Initialize();

}


/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update(GameManager* state) {

	// メインカメラ
	GameCamera_.UpdateMatrix();


	// スカイドーム
	skydome_->Update();


	// グラウンド
	ground_->Update();


	// プレイヤー
	player_->Update();


#ifdef _DEBUG

	ImGui::Begin("GameScene");
	ImGui::Text("GameCamera");
	ImGui::DragFloat3("Rotate", &GameCamera_.rotate.x, 0.01f);
	ImGui::DragFloat3("Translate", &GameCamera_.translate.x, 0.01f);
	ImGui::End();

#endif // _DEBUG
}


/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void GameScene::BackSpriteDraw() {


}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void GameScene::ModelDraw() {

	// スカイドーム
	skydome_->Draw(GameCamera_);

	// グラウンド
	ground_->Draw(GameCamera_);

	// プレイヤー
	player_->Draw(GameCamera_);

}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void GameScene::FrontSpriteDraw() {


}