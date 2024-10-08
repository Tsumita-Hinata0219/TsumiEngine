#pragma once

#include "../Collider/Segment/SegmentCollider.h"
#include "../Collider/Sphere/SphereCollider.h"
#include "../Collider/Box/AABBCollider.h"
#include "../Collider/Box/OBBCollider.h"
#include "../Collider/Segment/SegmentCollider.h"
#include "../Collider/ColliderConfig.h"
#include "../IsCollision/IsCollision.h"

#include "../Component/CollisionComponent.h"
#include "../Event/CollisionEvent.h"
#include "../ColEventManager/ColEventManager.h"


#include "Math/MyMath.h"
#include "Math/Struct.h"
#include "GameObject/IObject/IObject.h"

#include <list>
#include <vector>

// 前方宣言
class CollisionComponent;


/* CollisionManagerクラス */
class CollisionManager {

private: // シングルトン

	// コンストラクタ、デストラクタ
	CollisionManager() = default;
	~CollisionManager() = default;
	CollisionManager(const CollisionManager&) = delete;
	const CollisionManager& operator=(const CollisionManager&) = delete;


public:

	// インスタンス取得
	static CollisionManager* GetInstance() {
		static CollisionManager instance;
		return &instance;
	}

	// 解放処理
	static void Finalize();

	// コライダーの登録
	void Register(CollisionShape* shape);

	// 更新処理
	void Update();


private:

	// コリジョン判定を行う
	void CheckCollisions();

	// 無効なポインタは削除
	void CheckAndCleanPointers();

	// ImGuiの描画
	void DrawImGui();


private:

	// コライダーのポインタ配列
	std::vector<CollisionShape*> shapes_;

};
