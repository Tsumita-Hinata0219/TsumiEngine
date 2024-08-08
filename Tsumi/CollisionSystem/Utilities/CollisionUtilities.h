#pragma once

#include "../../Project/Math/MyMath.h"
#include "../Shape/CollisionShape.h"


namespace ColUtil {

	// OBBのワールドマトリックス作成
	Matrix4x4 CreateOBBWorldMatrix(const Col::OBB& obb);

	// 射影の重複チェック
	bool TestAxis(const Vector3& axis, const Col::OBB& obb1, const Col::OBB& obb2);

	// 実際に重なってるかの計算
	bool projectionOverlap(const std::pair<float, float>& projection1, const std::pair<float, float>& projection2);

	// 頂点を軸に射影
	std::pair<float, float> OBBProjection(const Col::OBB& obb, const Vector3& axis);

	// OBBの設定
	Col::OBB SettingOBBProperties(Col::OBB& obb);

	// AABBの設定
	Col::AABB SettingAABBProperties(Col::AABB& aabb);

	// Capsuleの設定
	//Col::Sphere SettingCapusulePropertirs();
}
