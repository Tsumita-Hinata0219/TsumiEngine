#include "MonsBall.h"



// 初期化処理
void MonsBall::Initialize()
{
	// ノーマルマップ用テクスチャの読み込み
	normalMapTexHD_ = TextureManager::LoadTexture("normalMap.png");

	// モデルの初期化
	monsBall_ = make_unique<Model>();
	monsBall_->CreateFromObj("ball");
	monsBall_->SetModelDrawType(PhongNormalMap);
	monsBall_->SetNormalMapTex(normalMapTexHD_);

	// ワールドトランスフォームの初期化
	wt_.Initialize();

	// ライトの初期化
	light_.color = { 1.0f, 1.0f, 1.0f, 1.0f };
	light_.direction = { 0.0f, -1.0f, 0.0f };
	light_.intensity = 1.0f;
	light_.sininess = 100.0f;
	light_.enableLightting = true;
}


// 更新処理
void MonsBall::Update()
{
	// ワールドトランスフォームの更新
	wt_.UpdateMatrix();

	// 回転させる
	wt_.rotate.y += 0.02f;

	// ライトの設定
	monsBall_->SetDirectionalLight(light_);

#ifdef _DEBUG

	if (ImGui::TreeNode("MonsBall")) {

		ImGui::ColorEdit4("LightColor", &light_.color.x);
		ImGui::DragFloat3("LightDirection", &light_.direction.x, 0.01f, -1.0f, 1.0f);
		ImGui::DragFloat("LightIntensity", &light_.intensity, 0.01f, -1.0f, 1.0f);
		ImGui::DragFloat("LightSininess", &light_.sininess, 0.1f, 0.0f, 200.0f);
		ImGui::TreePop();
	}

#endif // _DEBUG
}


// 描画処理
void MonsBall::Draw(ViewProjection view)
{
	monsBall_->Draw(wt_, view);
}
