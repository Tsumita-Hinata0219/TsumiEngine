#include "SphereCollider.h"
#include "GameObject/IObject/IObject.h"


/// <summary>
/// パラメータ付きコンストラクタ
/// </summary>
SphereCollider::SphereCollider(IObject* setOwner)
{
	// オーナーと属性の設定
	this->owner_ = setOwner;
	this->attribute_ = int(this->owner_->GetAttribute());
}


/// <summary>
/// ImGuiの描画
/// </summary>
void SphereCollider::DrawImGui(const std::string& label)
{
	ImGui::DragFloat3((label + "_Center").c_str(), &this->data_.center.x, 0.0f);
	ImGui::DragFloat((label + "_Radius").c_str(), &this->data_.radius, 0.0f);
}
