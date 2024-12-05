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
	// this Sphere x other Sphere
	if (auto sphere = std::get_if<Collider::Sphere>(&other.GetData())) {
		
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
