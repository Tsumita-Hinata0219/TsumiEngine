#include "TestHuman.h"



// 初期化処理
void TestHuman::Init()
{
	// コンフィグマネージャー
	std::string groupName = "TestHuman";
	configManager_ = ConfigManager::GetInstance();
	configManager_->CreateGroup(groupName);
	configManager_->AddItem(groupName, "Test", 90);
	configManager_->AddItem(groupName, "Test", 900.0f);
	configManager_->AddItem(groupName, "Test", Vector3(1.0f, 2.0f, 3.0f));
	//configManager_->SaveFile(groupName);

	// モデルの読み込み
	modelManager_ = ModelManager::GetInstance();
	modelManager_->LoadModel("gLTF/TestHuman", "walk.gltf");
	humanModel_ = modelManager_->GetModel("walk");

	// トランスフォームの初期化設定
	humanTrans_.Init();
	humanTrans_.srt.rotate.y = ToRadians(180.0f);

	// ライトの初期設定
	light_.enable = true;
	light_.direction = Vector3::one;

	// 環境マップの初期設定
	enviroment_.textureHandle = TextureManager::LoadTexture("Texture", "airport_4k.dds");
	enviroment_.enable = true;
	enviroment_.scale = 1.0f;
}


// 更新処理
void TestHuman::Update()
{
	
#ifdef _DEBUG

	if (ImGui::TreeNode("TestHuman")) {

		// トランスフォーム
		humanTrans_.DrawImGui();

		// ライト
		ImGui::Text("");
		ImGui::Text("Light");
		light_.DrawImGui();

		// 環境マップ
		ImGui::Text("");
		ImGui::Text("Enviroment");
		enviroment_.DrawImGui();

		ImGui::TreePop();
	}

#endif // _DEBUG
}


// 描画処理
void TestHuman::Draw()
{
	// ライトの設定
	humanModel_->SetLightData(light_);
	// 環境マップの設定
	humanModel_->SetEnvironmentData(enviroment_);
	// ヒューマンモデルの描画
	humanModel_->DrawN(humanTrans_);
}
