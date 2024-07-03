#include "GameScene.h"



/// <summary>
/// コンストラクタ
/// </summary>
GameScene::GameScene() {}


/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene() {}


/// <summary>
/// 初期化処理
/// </summary>
void GameScene::Initialize() 
{
	/* ----- FileManager ファイルマネージャー ----- */
	FileManager::GetInstance()->LoadJsonFile("Json/", "honmei");

	/* ----- Camera カメラ ----- */
	camera_ = make_unique<Camera>();
	camera_->Initialize();
	camera_->rotate = { 0.2f, 0.0f, 0.0f };
	camera_->translate = { 0.0f, 6.0f, -20.0f };

	/* ----- Skydome 天球 ----- */
	Skydome::GetInstance()->Initialize();

	/* ----- Ground 床 ----- */
	Ground::GetInstance()->Initialize();

	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_ = make_unique<TestPostEffect>();
	testPostEffect_->Initialize();

	/* ----- TestHuman テストヒューマン ----- */
	testHuman_ = make_unique<TestHuman>();
	testHuman_->Init();
  
	/* ----- Player プレイヤー ----- */
	player_ = make_unique<Player>();
	player_->Initialize();

	/* ----- Enemy enemy ----- */
	enemy_ = make_unique<Enemy>();
	enemy_->Initialize();
	enemy_->SetPlayer(player_.get());
}


/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update(GameManager* state) 
{
	state;

	/* ----- Camera カメラ ----- */
	camera_->UpdateMatrix();

	/* ----- Skydome 天球 ----- */
	Skydome::GetInstance()->Update();

	/* ----- Ground 床 ----- */
	Ground::GetInstance()->Update();
	
	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_->Update();

	/* ----- TestHuman テストヒューマン ----- */
	testHuman_->Update();
	
	/* ----- Player プレイヤー ----- */
	player_->Update();

	/* ----- Enemy enemy ----- */
	enemy_->Update();

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
	Skydome::GetInstance()->Draw(camera_.get());

	/* ----- Ground 床 ----- */
	Ground::GetInstance()->Draw(camera_.get());

	/* ----- TestHuman テストヒューマン ----- */
	testHuman_->Draw(camera_.get());

	/* ----- Player プレイヤー ----- */
	player_->Draw3D(camera_.get());

	/* ----- Enemy enemy ----- */
	enemy_->Draw3D(camera_.get());
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void GameScene::FrontSpriteDraw() 
{
	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_->Draw(camera_.get());
}

