#pragma once

#include "../Collider/ColliderConfig.h"
#include "../Detect/CollisionDetect.h"

#include "Math/MyMath.h"
#include "Math/Struct.h"

#include "../Collider/Interface/ICollider.h"
#include "../Collider/Sphere/SphereCollider.h"

#include <list>
#include <vector>

// 前方宣言
class IObject;


// ファクトリ関数
//using ColliderFactory = std::function<std::unique_ptr<ICollider>(IObject*)>;


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

	// コライダー登録
	void Register(ICollider* collider);
	void Register(Collider::ColliderData* data, IObject* owner);



	// 登録されているShapeを削除する
	//void UnRegister(Col::ColData* data);

	// 更新処理
	void Update();


#pragma region Accessor アクセッサ


#pragma endregion 


private:

	// コリジョン判定を行う
	void CheckCollisions();

	// データの更新
	//void UpdateCollisionData();

	// ImGuiの描画
	void DrawImGui();

	// Shapeのインスタンスの取得
	//static const std::unordered_map<std::type_index, ColliderFactory>& GetColliderFactoryMap();


private:

	// コライダーポインタリスト
	std::list<ICollider*> pColliders_;
	std::map<Collider::ColliderData*, std::unique_ptr<ICollider>> pColliderMap_;
};
