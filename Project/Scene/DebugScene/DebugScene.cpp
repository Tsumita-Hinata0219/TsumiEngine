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
	//FileManager::GetInstance()->LoadJsonFile("Json/", "honmei");

	/* ----- Camera カメラ ----- */
	camera_.Init({ 0.2f, 0.0f, 0.0f }, { 0.0f, 5.0f, -15.0f });
	cameraManager_ = CameraManager::GetInstance();
	cameraManager_->ReSetData(camera_);
	
	/* ----- Skydome 天球 ----- */
	skydome_ = std::make_unique<Skydome>();
	skydome_->Init();

	/* ----- Ground 床 ----- */
	ground_ = std::make_unique<Ground>();
	ground_->Init();

	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_ = make_unique<TestPostEffect>();
	testPostEffect_->Initialize();

	/* ----- TestHuman テストヒューマン ----- */
	testHuman_ = make_unique<TestHuman>();
	testHuman_->Init();

	/* ----- ModelNewLoad モデルニューロード ----- */
	modelManager_ = ModelManager::GetInstance();
	modelManager_->LoadModel("Obj/Test", "Test.obj");
	demoModel_ = modelManager_->GetModel("Test");

	transformA_.Initialize();
	transformA_.srt.scale = { 1.0f,1.0f,1.0f };
	transformA_.srt.rotate = { 0.0f,0.0f,0.0f };
	transformA_.srt.translate = { -2.0f,0.0f,0.0f };

	/* ----- TestBaseObject テストベースオブジェクト ----- */
	testBaseObject_ = std::make_unique<TestBaseObject>();
	testBaseObject_->Init();
}



/// <summary>
/// 更新処理
/// </summary>
void DebugScene::Update(GameManager* state)
{
	state;

	/* ----- Camera カメラ ----- */
	camera_.Update();

	/* ----- Skydome 天球 ----- */
	skydome_->Update();

	/* ----- Ground 床 ----- */
	ground_->Update();

	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_->Update();

	/* ----- TestHuman テストヒューマン ----- */
	testHuman_->Update();

#ifdef _DEBUG

	ImGui::Begin("DebugScene");
	camera_.DrawImGui();
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
	//skydome_->draw3D();

	/* ----- Ground 床 ----- */
	//ground_->Draw3D();

	/* ----- TestHuman テストヒューマン ----- */
	//testHuman_->Draw();

	/* ----- ModelNewLoad モデルニューロード ----- */
	demoModel_->DrawN(transformA_);

	/* ----- TestBaseObject テストベースオブジェクト ----- */
	testBaseObject_->Draw3D();
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void DebugScene::FrontSpriteDraw()
{
	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_->Draw();
}