#include "EngineManual.h"



/// <summary>
/// デストラクタ
/// </summary>
EngineManual::~EngineManual() 
{


}


/// <summary>
/// 初期化処理
/// </summary>
void EngineManual::Initialize()
{
	uvCheckerHD_ = TextureManager::LoadTexture("uvChecker.png");
	otherTex_ = TextureManager::LoadTexture("normalMap.png");

	// モデルの初期化
	ballObj_ = make_unique<Model>();
	ballObj_->CreateFromObj("ball");
	ballObj_->SetNormalMapTex(otherTex_);
	ballWT_.Initialize();
	light_.color = { 1.0f, 1.0f, 1.0f, 1.0f };
	light_.direction = { 0.0f, -1.0f, 0.0f };
	//light_.SpecularFColor = { 1.0f, 1.0f, 1.0f };
	light_.intensity = 1.0f;
	light_.sininess = 140.0f;
	light_.enableLightting = true;
}


/// <summary>
/// 更新処理
/// </summary>
void EngineManual::Update(ViewProjection view) 
{
	ballWT_.UpdateMatrix();
	ballObj_->SetDirectionalLight(light_);


	ImGui::Begin("BallObj");
	ImGui::ColorEdit4("LightColor", &light_.color.x);
	ImGui::DragFloat3("LightDirection", &light_.direction.x, 0.01f, -1.0f, 1.0f);
	ImGui::DragFloat("LightIntensity", &light_.intensity, 0.01f, -1.0f, 1.0f);
	ImGui::DragFloat("LightSininess", &light_.sininess, 0.1f, 0.0f, 200.0f);
	ImGui::End();

#ifdef _DEBUG

	ImGui::Begin("BallObj");
	ImGui::ColorEdit4("LightColor", &light_.color.x);
	ImGui::DragFloat3("LightDirection", &light_.direction.x, 0.01f, -1.0f, 1.0f);
	ImGui::DragFloat("LightIntensity", &light_.intensity, 0.01f, -1.0f, 1.0f);
	ImGui::DragFloat("LightSininess", &light_.sininess, 0.1f, 0.0f, 200.0f);
	ImGui::End();

#endif // _DEBUG

}


/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void EngineManual::BackSpriteDraw(ViewProjection view) 
{


}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void EngineManual::ModelDraw(ViewProjection view) 
{
	ballObj_->Draw(ballWT_, view);
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void EngineManual::FrontSpriteDraw(ViewProjection view) 
{


}


/// <summary>
/// Audioに関する処理まとめたやつ
/// </summary>
void EngineManual::AudioUpdate() 
{



#ifdef _DEBUG



#endif // _DEBUG
}