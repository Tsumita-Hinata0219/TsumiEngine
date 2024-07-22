#include "DebugScene.h"



/// <summary>
/// コンストラクタ
/// </summary>
DebugScene::DebugScene() {}


/// <summary>
/// デストラクタ
/// </summary>
DebugScene::~DebugScene() {}


/// <summary>
/// 初期化処理
/// </summary>
void DebugScene::Initialize()
{
	/* ----- FileManager ファイルマネージャー ----- */
	FileManager::GetInstance()->LoadJsonFile("Json/", "honmei");

	/* ----- Camera カメラ ----- */
	camera_ = make_unique<Camera>();
	camera_->Initialize();
	camera_->rotate = { 0.2f, 0.0f, 0.0f };
	camera_->translate = { 0.0f, 5.0f, -15.0f };
	cameraManager_ = CameraManager::GetInstance();
	cameraResource_.Init();
	

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


	/* ----- ModelNewLoad モデルニューロード ----- */
	modelManager_ = ModelManager::Getinstance();
	modelManager_->LoadModel("Test", "Test.obj");
	demoModel_ = modelManager_->GetModel("Test");

	transformA_.Initialize();
	transformA_.srt.scale = { 1.0f,1.0f,1.0f };
	transformA_.srt.rotate = { 0.0f,0.0f,0.0f };
	transformA_.srt.translate = { -2.0f,0.0f,0.0f };

	/*light_.eneble = false;
	environment_.enable = false;*/
}



/// <summary>
/// 更新処理
/// </summary>
void DebugScene::Update(GameManager* state)
{
	state;

	/* ----- Camera カメラ ----- */
	camera_->UpdateMatrix();
	cameraManager_->ReSetData(cameraResource_);

	/* ----- Skydome 天球 ----- */
	Skydome::GetInstance()->Update();

	/* ----- Ground 床 ----- */
	Ground::GetInstance()->Update();

	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_->Update();

	/* ----- TestHuman テストヒューマン ----- */
	testHuman_->Update();

#ifdef _DEBUG

	ImGui::Begin("DebugScene");

	ImGui::Text("");
	ImGui::Text("Camera");
	ImGui::DragFloat3("Rotate", &camera_->rotate.x, 0.01f);
	ImGui::DragFloat3("Translate", &camera_->translate.x, 0.01f);
	ImGui::Text("");

	ImGui::End();


	ImGui::Begin("Test");
	transformA_.DrawImGui();
	light_.DrawImGui();
	environment_.DrawImGui();
	ImGui::End();

#endif // _DEBUG
}


/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void DebugScene::BackSpriteDraw()
{

}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void DebugScene::ModelDraw()
{
	/* ----- Skydome 天球 ----- */
	//Skydome::GetInstance()->Draw(camera_.get());

	/* ----- Ground 床 ----- */
	//Ground::GetInstance()->Draw(camera_.get());

	/* ----- TestHuman テストヒューマン ----- */
	//testHuman_->Draw(camera_.get());

	/* ----- ModelNewLoad モデルニューロード ----- */
	demoModel_->DrawN(transformA_);
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void DebugScene::FrontSpriteDraw()
{
	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_->Draw(camera_.get());
}