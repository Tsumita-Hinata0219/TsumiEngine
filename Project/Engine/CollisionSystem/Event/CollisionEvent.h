#pragma once

#include "Math/MyMath.h"

// 前方宣言
class CollisionComponent;

/* コリジョンが発生したときに必要な情報を保持するためのクラス */
class CollisionEvent {

public:

	// コンストラクタ、デストラクタ
	CollisionEvent() {};
	~CollisionEvent() {};

	// パラメータ付きコンストラクタ
	CollisionEvent(CollisionComponent* comp1, CollisionComponent* comp2);


#pragma region Accessor アクセッサ

	// コンポーネント
	CollisionComponent* GetComponent1() const { return this->component1_; }
	CollisionComponent* GetComponent2() const { return this->component2_; }

	// 衝突点
	const Vector3& GetImpactPoint() const { return impactPoint_; }
	void SetImpactPoint(const Vector3& point) { impactPoint_ = point; }
	
	// 衝突法線
	const Vector3& GetCollisionNormal() const { return collisionNormal_; }
	void SetCollisionNormal(const Vector3& normal) { collisionNormal_ = normal; }
	

#pragma endregion 


private:

	// 衝突したオブジェクト
	CollisionComponent* component1_ = nullptr;
	CollisionComponent* component2_ = nullptr;

	// 衝突点
	Vector3 impactPoint_{};

	// 衝突法線
	Vector3 collisionNormal_{};
};

