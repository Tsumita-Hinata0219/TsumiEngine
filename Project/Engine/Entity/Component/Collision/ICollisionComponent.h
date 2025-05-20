#pragma once

#include "Math/MyMath.h"
#include "../../Actor/Interface/IActor.h"
#include "../../TransformNode/Node/TransformNode.h"
#include "../../Collision/Collider/IEntityCollider.h"
#include "../../Collision/Collider/CollisionSphere.h"
#include "../../Collision/Collider/CollisionAABB.h"


/* 衝突判定用のコンポーネント */
class ICollisionComponent {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ICollisionComponent();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ICollisionComponent() = default;

	/// <summary>
	/// 生成
	/// </summary>
	void Create(const std::string& name);
	
	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Init() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update(float deltaTime) { deltaTime; };


#pragma region Accessor 

	// 名前
	std::string Get_Name() const { return name_; }

	// Owner
	void SetOwner(std::weak_ptr<IActor> setOwner) { owner_ = setOwner; }

	// Collider
	virtual std::shared_ptr<Entity::Collision::IEntityCollider> GetCollider() const = 0;

#pragma endregion 


protected:

	// Componentを持つ親Actor
	std::weak_ptr<IActor> owner_;

	// Componentの名前
	std::string name_;

};

