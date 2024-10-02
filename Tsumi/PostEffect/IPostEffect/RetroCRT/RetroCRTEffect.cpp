#include "RetroCRTEffect.h"



// 初期化処理
void RetroCRTEffect::Init()
{
	Create();


}


// 描画処理
void RetroCRTEffect::Draw()
{
	// MtlBufferにMtlを書き込む
	mtlBuffer_.Map();
	mtlBuffer_.WriteData(&mtlData_);
	mtlBuffer_.UnMap();

	// コマンドコール
	CommandCall();
}


// ImGuiの描画
void RetroCRTEffect::DrawImGui(std::string name)
{
#ifdef _DEBUG

	// Labelを追加する場合は追加
	label_ = label_ + name;

	if (ImGui::TreeNode((label_ + "RetroCRT").c_str())) {

		ImGui::ColorEdit4("Color", &mtlData_.color.x);
		ImGui::DragFloat("Threshold", &mtlData_.threshold, 0.01f, 0.0f, 1.0f);
		ImGui::DragFloat("Thinkness", &mtlData_.thinkness, 0.01f, 0.0f, 1.0f);

		ImGui::TreePop();
	}

#endif // _DEBUG
}


// コマンドコール
void RetroCRTEffect::CommandCall()
{
}
