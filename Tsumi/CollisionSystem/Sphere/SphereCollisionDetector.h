#pragma once

#include "../Detector/CollisionDetector.h"

/* 球形のコライダー用の衝突判定 */
class SphereCollisionDetector : public CollisionDetector {

public:

	//// コンストラクタ、デストラクタ
	//SphereCollisionDetector() {};
	//~SphereCollisionDetector() {};

	///// <summary>
	///// 衝突判定ロジックを実装する関数
	///// </summary>
	//bool Detect(const CollisionDetector& other) const override {
	//	return other.detectSphere(*this);
	//}
	//bool detectSphere(const SphereCollisionDetector& other) const override {
	//	return Collision::IsCollision(this->sphere_, other.sphere_);
	//}


private:

	//Sphere sphere_{};
};

