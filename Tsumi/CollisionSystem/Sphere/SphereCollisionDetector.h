#pragma once

#include "../Detector/CollisionDetector.h"

/* 球形のコライダー用の衝突判定 */
class SphereCollisionDetector : public CollisionDetector {

public:

	// コンストラクタ、デストラクタ
	SphereCollisionDetector() {};
	~SphereCollisionDetector() {};

	/// <summary>
	/// 衝突判定ロジックお実装する関数
	/// </summary>
	bool Detect() override;

};

