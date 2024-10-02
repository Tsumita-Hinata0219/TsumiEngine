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
	if (ImGui::TreeNode((name + "RetroCRT").c_str())) {
		mtlData_.DrawImGui(name);
		ImGui::TreePop();
	}
#endif // _DEBUG
}


// コマンドコール
void RetroCRTEffect::CommandCall()
{


}
