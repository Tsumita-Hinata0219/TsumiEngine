#pragma once

#include "../Detector/CollisionDetector.h"

/* 抽象的なコライダークラス */
class Collider {

public:

	Collider(CollisionDetector* d) : detector_(d) {};

	// 衝突判定を返す
	bool DetectCollision(const Collider& other) const {
		return detector_->Detect(*other.detector_);
	}


private:

	CollisionDetector* detector_;
};