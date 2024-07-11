#include "BoxFilterEffect.h"



// 初期化処理
void BoxFilterEffect::Initialize()
{
	Microsoft::WRL::ComPtr<ID3D12Resource> stv =
		RTVManager::GetRTV("PostEffect")->GetRTVPrope().Resources.Get();

}


// 描画処理
void BoxFilterEffect::Draw()
{

}


// ImGuiの描画
void BoxFilterEffect::DrawImGui(std::string name)
{
#ifdef _DEBUG

	// Labelを追加する場合は追加
	label_ = label_ + name;

	if (ImGui::TreeNode((label_ + "BoxFilter").c_str())) {

		ImGui::ColorEdit4("Color", &mtlData_.color.x);

		ImGui::TreePop();
	}

#endif // _DEBUG
}
