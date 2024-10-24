#pragma once

#include "../Structure/CollisionStructures.h"
#include "../Collider/Segment/SegmentCollider.h"
#include "../Collider/Sphere/SphereCollider.h"
#include "../Collider/Box/AABBCollider.h"
#include "../Collider/Box/OBBCollider.h"
#include "../Collider/Segment/SegmentCollider.h"
#include "Math/MyMath.h"

#include <array>


namespace GeometryCollision {

	// OBBのワールドマトリックス作成
	Matrix4x4 CreateOBBWorldMatrix(const OBB& obb);

	// 射影の重複チェック
	bool TestAxis(const Vector3& axis, const OBB& obb1, const OBB& obb2);

	// 実際に重なってるかの計算
	bool projectionOverlap(const std::pair<float, float>& projection1, const std::pair<float, float>& projection2);

	// 頂点を軸に射影
	std::pair<float, float> obbProjection(const OBB& obb, const Vector3& axis);

	// OBBの設定
	OBB SettingOBBProperties(OBBCollider* c);

	// AABBの設定
	AABB SettingAABBProperties(AABBCollider* c);

	// Capsuleの設定
	Capsule SettingCapusulePropertirs();
}