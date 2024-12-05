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
using ColliderFactory = std::function<std::unique_ptr<ICollider>(IObject*)>;


/* CollisionManagerクラス */
class CollisionManager {

private: // シングルトン

	CollisionManager() = default;
	~CollisionManager() = default;
	CollisionManager(const CollisionManager&) = delete;
	const CollisionManager& operator=(const CollisionManager&) = delete;


public:

	/// <summary>
	/// インスタンス取得
	/// </summary>
	static CollisionManager* GetInstance() {
		static CollisionManager instance;
		return &instance;
	}

	/// <summary>
	/// コライダー登録
	/// </summary>
	void Register(ICollider* pCollider);

	/// <summary>
	/// 登録されているShapeを削除する
	/// </summary>
	void UnRegister(Collider::ColliderData* data);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();


#pragma region Accessor アクセッサ


#pragma endregion 


private:

	/// <summary>
	/// コリジョン判定を行う
	/// </summary>
	void CheckCollisions();

	/// <summary>
	/// ImGuiの描画LD
	/// </summary>
	void DrawImGui();

	/// <summary>
	/// Colliderのインスタンスの取得
	/// </summary>
	static const std::unordered_map<std::type_index, ColliderFactory>& GetColliderFactoryMap();


private:

	// コライダーポインタリスト
	//std::map<Collider::ColliderData*, std::unique_ptr<ICollider>> pColliderMap_;
	std::list<ICollider*> pColliders_;
};
