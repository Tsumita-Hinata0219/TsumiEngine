#include "MonsBall.h"



// 初期化処理
void MonsBall::Initialize()
{
	// ノーマルマップ用テクスチャの読み込み
	normalMapTexHD_ = TextureManager::LoadTexture("normalMap.png");


	ModelDrawType type[4] = { Non, Lambert, Phong, PhongNormalMap };
	float pos[4] = { -4.5f, -1.5f, 1.5f, 4.5f };

	// モデルの初期化
	for (int i = 0; i < 4; ++i) {

		// モデルの初期化
		monsBall_[i] = make_unique<Model>();
		monsBall_[i]->CreateFromObj("ball");
		monsBall_[i]->SetModelDrawType(type[i]);

		if (i == 3) {
			monsBall_[i]->SetNormalMapTex(normalMapTexHD_);
		}

		// ワールドトランスフォームの初期化
		wt_[i].Initialize();
		wt_[i].translate.x = pos[i];
	}

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
	// ワールドトランスフォームの更新 & 回転させる
	for (int i = 0; i < 4; ++i) {
		wt_[i].UpdateMatrix();
		wt_[i].rotate.y += 0.01f;
	}
	for (int i = 1; i < 4; ++i) {
		monsBall_[i]->SetDirectionalLight(light_);
	}

#ifdef USE_IMGUI

	if (ImGui::TreeNode("MonsBall")) {

		ImGui::ColorEdit4("LightColor", &light_.color.x);
		ImGui::DragFloat3("LightDirection", &light_.direction.x, 0.01f, -1.0f, 1.0f);
		ImGui::DragFloat("LightIntensity", &light_.intensity, 0.01f, -1.0f, 1.0f);
		ImGui::DragFloat("LightSininess", &light_.sininess, 0.1f, 0.0f, 200.0f);
		ImGui::TreePop();
	}

#endif // USE_IMGUI
}


// 描画処理
void MonsBall::Draw(ViewProjection view)
{
	for (int i = 0; i < 4; ++i) {
		monsBall_[i]->Draw(wt_[i], view);
	}
}
