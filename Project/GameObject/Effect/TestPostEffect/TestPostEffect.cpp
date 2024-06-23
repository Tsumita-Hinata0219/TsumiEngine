#include "TestPostEffect.h"



// 初期化処理
void TestPostEffect::Initialize()
{
	// リソースなどを作成
	Create();
}


// 更新処理
void TestPostEffect::Update()
{



#ifdef _DEBUG

	/*if (ImGui::TreeNode("TestPostEffect")) {

		ImGui::ColorEdit4("Color", &material_.mtlData.color.x);
		if (ImGui::Button("None")) {

			material_.mtlData.type = int(PostEffectType::None);
		}
		if (ImGui::Button("GrayScale")) {

			material_.mtlData.type = int(PostEffectType::GrayScale);
		}
		if (ImGui::Button("Sepia")) {

			material_.mtlData.type = int(PostEffectType::Sepia);
		}
		if (ImGui::Button("Vignetting")) {

			material_.mtlData.type = int(PostEffectType::Vignetting);
		}
		if (ImGui::Button("Smoothing")) {

			material_.mtlData.type = int(PostEffectType::Smoothing);
		}
		if (ImGui::Button("GaussianFilter")) {

			material_.mtlData.type = int(PostEffectType::GaussianFilter);
		}
		if (ImGui::Button("OutLine")) {

			material_.mtlData.type = int(PostEffectType::OutLine);
		}

		ImGui::TreePop();
	}*/

#endif // _DEBUG
}


// 描画処理
void TestPostEffect::Draw()
{

	// コマンドコール
	CommandCall();
}
