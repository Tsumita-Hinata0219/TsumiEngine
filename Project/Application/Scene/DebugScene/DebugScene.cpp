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
	/* ----- Camera カメラ ----- */
	camera_.Init({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
	cameraManager_ = CameraManager::GetInstance();
	cameraManager_->ReSetData(camera_);
	
	/* ----- Skybox 天箱 ----- */
	skybox_ = std::make_unique<Skybox>();
	uint32_t dds = TextureManager::LoadTexture("Texture", "DemoSkybox.dds");
	skybox_->Init(dds);

	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_ = make_unique<TestPostEffect>();
	testPostEffect_->Init();

	/* ----- DemoParticle デモパーティクル ----- */
	dParticleInstanceNum_ = 10;
	dParticle_ = std::make_unique<GPUParticle>();
	dParticle_->Init(dParticleInstanceNum_);
	transforms_.resize(dParticleInstanceNum_);
	for (auto& element : transforms_) {
		element.Init();
		element.srt.translate.z = 5.0f;
	}
	materials_.resize(dParticleInstanceNum_);
	for (auto& element : materials_) {
		element.color = Samp::Color::WHITE;
		element.uvTransform = Matrix4x4::identity;
	}
}



/// <summary>
/// 更新処理
/// </summary>
void DebugScene::Update(GameManager* state)
{
	state;

	/* ----- Camera カメラ ----- */
	camera_.Update();

	/* ----- Skybox 天箱 ----- */
	skybox_->Update();

	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_->Update();

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
	/* ----- Skybox 天箱 ----- */
	//skybox_->Draw();

	/* ----- DemoParticle デモパーティクル ----- */
	dParticle_->Draw(transforms_, materials_);
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void DebugScene::FrontSpriteDraw()
{
	/* ----- TestPostEffect テストポストエフェクト ----- */
	testPostEffect_->Draw();
}