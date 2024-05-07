#include "GameScene.h"



/// <summary>
/// コンストラクタ
/// </summary>
GameScene::GameScene() {

}


/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene() 
{

}


/// <summary>
/// 初期化処理
/// </summary>
void GameScene::Initialize() 
{
	/* ----- Camera カメラ ----- */
	camera_ = make_unique<Camera>();
	camera_->Initialize();
	camera_->rotate = { 0.2f, 0.0f, 0.0f };
	camera_->translate = { 0.0f, 20.0f, -75.0f };


	/* ----- Skydome 天球 ----- */
	Skydome::GetInstance()->Initialize();

	/* ----- Ground 床 ----- */
	Ground::GetInstance()->Initialize();

	postEffect_ = make_unique<PostEffect>();
	postEffect_->Initialize();

	sp_ = make_unique<Sprite>();
	sp_->Initialize();
	wt_.Initialize();
	sp_->SetSize(Vector2(1280.0f, 720.0f));
}


/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update(GameManager* state) 
{

	state;

	wt_.UpdateMatrix();

	/* ----- Skydome 天球 ----- */
	Skydome::GetInstance()->Update();


	/* ----- Ground 床 ----- */
	Ground::GetInstance()->Update();


#ifdef _DEBUG

	ImGui::Begin("GameScene");

	ImGui::Text("");
	ImGui::Text("Camera");
	ImGui::DragFloat3("Rotate", &camera_->rotate.x, 0.01f);
	ImGui::DragFloat3("Translate", &camera_->translate.x, 0.01f);
	ImGui::Text("");

	ImGui::End();

#endif // _DEBUG
}


/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void GameScene::BackSpriteDraw() 
{

}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void GameScene::ModelDraw() 
{

	/* ----- Skydome 天球 ----- */
	//Skydome::GetInstance()->Draw(camera_.get());

	/* ----- Ground 床 ----- */
	Ground::GetInstance()->Draw(camera_.get());

	//postEffect_->Draw();
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void GameScene::FrontSpriteDraw() 
{
	sp_->Draw(1, wt_, camera_.get());
	
}


