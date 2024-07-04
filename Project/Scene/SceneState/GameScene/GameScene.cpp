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

	/* ----- Skybox 天箱 ----- */
	Skybox::GetInstance()->Initialize();

	/* ----- Ground 床 ----- */
	Ground::GetInstance()->Initialize();

	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_ = make_unique<TestPostEffect>();
	testPostEffect_->Initialize();

	/* ----- TestObject テストオブジェクト ----- */
	testObject_ = make_unique<TestObject>();
	testObject_->Init();

	/* ----- TestAnimCube テストアニメーションキューブ ----- */
	testAnimCube_ = make_unique<TestAnimationCube>();
	testAnimCube_->Init();

	/* ----- TestHuman テストヒューマン ----- */
	testHuman_ = make_unique<TestHuman>();
	testHuman_->Init();
  
	/* ----- TestJsonObject テストJsonオブジェクト ----- */
	testJsonObject_ = make_unique<TestJsonObject>();
	testJsonObject_->Initialize();

	/* ----- newModel 新しいモデル描画形式 ----- */
	ModelManager::Getinstance()->AddModel("Test", Model::LoadObjFileAssimpVer("Test", "Test.obj"));
	transform_.Initialize();
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

	/* ----- Skybox 天箱 ----- */
	Skybox::GetInstance()->Update();

	/* ----- Ground 床 ----- */
	Ground::GetInstance()->Update();
	
	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_->Update();

	/* ----- TestObject テストオブジェクト ----- */
	testObject_->Update();

	/* ----- TestAnimCube テストアニメーションキューブ ----- */
	testAnimCube_->Update();

	/* ----- TestHuman テストヒューマン ----- */
	testHuman_->Update();
	
	/* ----- TestJsonObject テストJsonオブジェクト ----- */
	testJsonObject_->Update();

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

	/* ----- Skybox 天箱 ----- */
	Skybox::GetInstance()->Draw(camera_.get());

	/* ----- Ground 床 ----- */
	//Ground::GetInstance()->Draw(camera_.get());

	/* ----- TestObject テストオブジェクト ----- */
	//testObject_->Draw(camera_.get());

	/* ----- TestAnimCube テストアニメーションキューブ ----- */
	//testAnimCube_->Draw(camera_.get());

	/* ----- TestHuman テストヒューマン ----- */
	testHuman_->Draw(camera_.get());

	/* ----- TestJsonObject テストJsonオブジェクト ----- */
	//testJsonObject_->Draw(camera_.get());

	/* ----- newModel 新しいモデル描画形式 ----- */
	//PipeLineManager::PipeLineCheckAndSet(PipeLineType::Lambert);
	//ModelManager::Getinstance()->GetModel("Test")->DrawN(transform_, camera_.get());
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void GameScene::FrontSpriteDraw() 
{
	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_->Draw(camera_.get());
}

