#pragma once

#include "Math/MyMath.h"
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
	//Col::AABB SettingAABBProperties(Col::AABB& aabb);

	// Capsuleの設定
	//Col::Sphere SettingCapusulePropertirs();

	// コライダー間の最寄点を計算する関数
	Vector3 GetClosestPoint(const Col::Sphere& sphere, const Vector3& point);
	Vector3 GetClosestPoint(const Col::AABB& aabb, const Vector3& point);
	Vector3 GetClosestPoint(const Col::OBB& obb, const Vector3& point);
	Vector3 GetClosestPoint(const Col::Segment& segment, const Vector3& point);
	Vector3 GetClosestPoint(const Col::Capsule& capsule, const Vector3& point);

	// コライダー間の交差時に押し出すためのベクトルを計算する関数
	Vector3 GetPenetrationPush(const Col::Sphere& sphere1, const Col::Sphere& sphere2);
	Vector3 GetPenetrationPush(const Col::Sphere& sphere, const Col::AABB& aabb);
	Vector3 GetPenetrationPush(const Col::Sphere& sphere, const Col::OBB& obb);
	Vector3 GetPenetrationPush(const Col::AABB& aabb1, const Col::AABB& aabb2);
	Vector3 GetPenetrationPush(const Col::AABB& aabb, const Col::Sphere& sphere);
	Vector3 GetPenetrationPush(const Col::AABB& aabb, const Col::OBB& obb);
	Vector3 GetPenetrationPush(const Col::OBB& obb1, const Col::OBB& obb2);
	Vector3 GetPenetrationPush(const Col::OBB& obb, const Col::Sphere& sphere);
	Vector3 GetPenetrationPush(const Col::OBB& obb, const Col::AABB& aabb);
	Vector3 GetPenetrationPush(const Col::Segment& segment, const Col::Sphere& sphere);
	Vector3 GetPenetrationPush(const Col::Capsule& capsule, const Col::Sphere& sphere);
	Vector3 GetPenetrationPush(const Col::Segment& segment, const Col::AABB& aabb);
	Vector3 GetPenetrationPush(const Col::Capsule& capsule, const Col::AABB& aabb);
	Vector3 GetPenetrationPush(const Col::Capsule& capsule1, const Col::Capsule& capsule2);
	Vector3 GetPenetrationPush(const Col::Segment& segment1, const Col::Segment& segment2);
}
