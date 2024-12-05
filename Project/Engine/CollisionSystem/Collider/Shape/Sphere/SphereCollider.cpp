#include "SphereCollider.h"
#include "GameObject/IObject/IObject.h"


/// <summary>
/// パラメータ付きコンストラクタ
/// </summary>
SphereCollider::SphereCollider(IObject* setOwner)
{
	// オーナーと属性の設定
	owner_ = setOwner;
	// 属性を設定
	attribute_ = {
		owner_->GetCategory(), owner_->GetType()
	};
}


/// <summary>
/// 更新処理
/// </summary>
void SphereCollider::Update()
{
}


/// <summary>
/// 衝突判定
/// </summary>
bool SphereCollider::Intersects(const ICollider& other)
{
	ColliderDataType type = other.GetData();
	
	if (auto sphere = std::get_if<Collider::Sphere>(&type)) {
		// 判定結果を返す
		return Detect::Intersects(this->data_, *sphere);
	}
	return false;
}


/// <summary>
/// ImGuiの描画
/// </summary>
void SphereCollider::DrawImGui(const std::string& label)
{
	ImGui::DragFloat3((label + "_Center").c_str(), &this->data_.center.x, 0.0f);
	ImGui::DragFloat((label + "_Radius").c_str(), &this->data_.radius, 0.0f);
}
