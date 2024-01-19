#pragma once

#include "SphereCollider.h"
#include "OBBCollider.h"
#include "AABBCollider.h"
#include "SegmentCollider.h"
#include "MyMath.h"
#include "Struct.h"
#include "IsCollision/IsCollision.h"

#include <list>
using namespace std;



/* CollisionManagerクラス */
class CollisionManager {

public:

	/// <summary>
	/// 登録されたすべてのコライダーに対して衝突を検出する。
	/// </summary>
	void CheckAllCollision();

    /// <summary>
    /// 各種コライダーをリストに登録するメソッド
    /// </summary>
    void ColliderSpherePushBack(SphereCollider* collider) { sphereColliders_.push_back(collider); }
    void ColliderSegmentPushBack(SegmentCollider* collider) { segmentColliders_.push_back(collider); }
    void ColliderAABBPushBack(AABBCollider* collider) { aabbColliders_.push_back(collider); }
    void ColliderOBBPushBack(OBBCollider* collider) { obbColliders_.push_back(collider); }

    /// <summary>
    /// 登録されたコライダーリストをクリアするメソッド
    /// </summary>
    void ClliderClear()	{
		sphereColliders_.clear();
        segmentColliders_.clear();
		aabbColliders_.clear();
        obbColliders_.clear();
	}


private:

    // -------------------------------------------------------------------------
    // 衝突検出メソッド
    // -------------------------------------------------------------------------
    // 各種コライダー同士の衝突検出メソッド
    // -------------------------------------------------------------------------
    void DetectSphere2SphereList(list<SphereCollider*>::iterator itrA);
    void DetectAABB2AABBList(list<AABBCollider*>::iterator itrA);
    void DetectAABB2SphereList(list<AABBCollider*>::iterator itrA, list<SphereCollider*>::iterator itrB);
    void DetectAABB2SegmentList(list<AABBCollider*>::iterator itrA, list<SegmentCollider*>::iterator itrB);
    void DetectOBB2SphereList(list<OBBCollider*>::iterator itrA, list<SphereCollider*>::iterator itrB);
    void DetectOBB2SegmentList(list<OBBCollider*>::iterator itrA, list<SegmentCollider*>::iterator itrB);
    void DetectOBB2OBBList(list<OBBCollider*>::iterator itrA);


    // -------------------------------------------------------------------------
    // 衝突検出と応答メソッド
    // -------------------------------------------------------------------------
    // 2つのコライダーの衝突検出と応答メソッド
    // -------------------------------------------------------------------------
    void CheckCollisionSpherexSphere(SphereCollider* cA, SphereCollider* cB);
    void CheckCollisionAABBxAABB(AABBCollider* cA, AABBCollider* cB);
    void CheckCollisionAABBxSphere(AABBCollider* cA, SphereCollider* cB);
    void CheckCollisionAABBxSegment(AABBCollider* cA, SegmentCollider* cB);
    void CheckCollisionOBBxSphere(OBBCollider* cA, SphereCollider* cB);
    void CheckCollisionOBBxSegment(OBBCollider* cA, SegmentCollider* cB);
    void CheckCollisionOBBxOBB(OBBCollider* cA, OBBCollider* cB);


private:

	// コライダーリスト
	list<SphereCollider*> sphereColliders_;
	list<SegmentCollider*> segmentColliders_;
    list<AABBCollider*> aabbColliders_;
    list<OBBCollider*> obbColliders_;
};

