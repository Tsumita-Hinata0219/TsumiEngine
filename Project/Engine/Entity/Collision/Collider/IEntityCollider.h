#pragma once

#include "Math/MyMath.h"


namespace Entity {
namespace Collision {

// 前方宣言
class CollisionManager;
class CollisionSphere;
class CollisionAABB;

// 型識別用
enum class ColliderTypeID {
	None = -1,
	Sphere,
	AABB,
	Count // 型数管理に使う
};


/* Colliderの基底クラス */
class IEntityCollider : public std::enable_shared_from_this<IEntityCollider> {

protected:

	// 親マネージャー
	CollisionManager* pManager_ = nullptr;
	// 活動フラグ
	bool isActive_ = false;


public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	IEntityCollider();

	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual  ~IEntityCollider() = default;

	/// <summary>
	/// 識別IDのGetter
	/// </summary>
	virtual ColliderTypeID GetTypeID() const = 0;

	/// <summary>
	/// 判定処理
	/// </summary>
	virtual bool Intersects(const IEntityCollider&  other) const = 0;

	/// <summary>
	/// ダブルディスパッチ
	/// </summary>
	virtual bool IntersectsWith(const CollisionSphere& other) const = 0;
	virtual bool IntersectsWith(const CollisionAABB& other) const  = 0;


#pragma region Accessor

	/// <summary>
	/// 共有ポインタを取得する関数
	/// </summary>
	std::shared_ptr<IEntityCollider> GetSharedPtr() {
		return shared_from_this();
	}

#pragma endregion

};
}
}