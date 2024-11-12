#include "CollisionShapeSphere.h"
#include "../AABB/CollisionShapeAABB.h"
#include "../../Detect/CollisionDetect.h"
#include "../../Component/CollisionComponent.h"



// パラメータ付きコンストラクタ
CollisionShapeSphere::CollisionShapeSphere(CollisionComponent* comp)
{
	// コンポーネントの設定
	component_ = comp;
}
CollisionShapeSphere::CollisionShapeSphere(CollisionComponent* comp, Col::Sphere* setData)
{
	// コンポーネントのの設定
	component_ = comp;
	// データの設定
	sphere_ = *setData;
}


// 衝突判定処理
bool CollisionShapeSphere::Intersects(const CollisionShape& other) const
{
	return other.Intersects(*this);
}
bool CollisionShapeSphere::Intersects(const CollisionShapeSphere& other) const
{
	// Sphere x Sphere
	ColShapeData s1 = this->GetData();
	ColShapeData s2 = other.GetData();

	// 型が一致するか確認してデータを取り出す
	if (auto sphere1 = std::get_if<Col::Sphere>(&s1)) {
		if (auto sphere2 = std::get_if<Col::Sphere>(&s2)) {
			return Detect::Intersects(*sphere1, *sphere2);
		}
		else {
			throw std::invalid_argument("Other shape is not a Sphere");
		}
	}
	else {
		throw std::invalid_argument("This shape is not an AABB");
	}
}
bool CollisionShapeSphere::Intersects(const CollisionShapeAABB& other) const
{
	// Sphere x AABB
	ColShapeData a1 = other.GetData();
	ColShapeData s1 = this->GetData();

	// 型が一致するか確認してデータを取り出す
	if (auto aabb = std::get_if<Col::AABB>(&a1)) {
		if (auto sphere = std::get_if<Col::Sphere>(&s1)) {
			return Detect::Intersects(*aabb, *sphere);
		}
		else {
			throw std::invalid_argument("Other shape is not a Sphere");
		}
	}
	else {
		throw std::invalid_argument("This shape is not an AABB");
	}
}


// コライダーの境界ボックスを求める
void CollisionShapeSphere::CalcBounding()
{
	// Col::AABBの各要素を求める
	Vector3 center = this->sphere_.center;
	float rad = this->sphere_.radius;
	Vector3 min = this->sphere_.center + Vector3(rad, rad, rad);
	Vector3 max = this->sphere_.center - Vector3(rad, rad, rad);
	uint32_t id = this->sphere_.id;

	// 境界ボックスに情報を挿入
	this->bounding_.id = id;
	this->bounding_.center = center;
	this->bounding_.min = min;
	this->bounding_.max = max;
}


// ImGuiの描画
void CollisionShapeSphere::DrawImGui(const std::string& label)
{
	ImGui::DragFloat3((label + "_Center").c_str(), &this->sphere_.center.x, 0.0f);
	ImGui::DragFloat((label + "_Radius").c_str(), &this->sphere_.radius, 0.0f);
}
