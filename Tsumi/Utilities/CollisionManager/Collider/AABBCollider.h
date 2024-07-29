#pragma once

#include<cstdint>

#include "../CollisionStructures/CollisionStructures.h"
#include "ColliderConfig.h"

#include "../../Project/Math/MyMath.h"
#include "../../../Transform/Transform.h"

//
//class AABBCollider {
//
//public:
//
//	/// <summary>
//	/// 衝突時コールバック関数
//	/// </summary>
//	virtual void OnCollision(uint32_t id) = 0;
//
//	/// <summary>
//	/// ワールド座標の取得
//	/// </summary>
//	virtual Vector3 GetWorldPosition() = 0;
//
//#pragma region AABB
//
//	/// <summary>
//	/// OBBの取得
//	/// </summary>
//	AABB GetAABB() { return aabb_; }
//
//	/// <summary>
//	/// OBBの設定
//	/// </summary>
//	void SetAABB(AABB aabb) { aabb_ = aabb; }
//
//#pragma endregion 
//
//#pragma region Size
//
//	/// <summary>
//	/// Sizeの取得
//	/// </summary>
//	Vector3 GetSize() { return size_; }
//
//	/// <summary>
//	/// Sizeの設定
//	/// </summary>
//	void SetSize(Vector3 size) { size_ = size; }
//
//#pragma endregion
//
//#pragma region ID
//
//	/// <summary>
//	/// IDの取得
//	/// </summary>
//	uint32_t GetID() { return id_; }
//
//	/// <summary>
//	/// IDの設定
//	/// </summary>
//	void SetID(uint32_t id) { id_ = id; }
//
//#pragma endregion 
//
//#pragma region CollisionAttribute
//
//	/// <summary>
//	/// collisionAttributeの取得
//	/// </summary>
//	uint32_t GetCollosionAttribute() const { return collisionAttribute_; }
//
//	/// <summary>
//	/// collisionAttributeの設定
//	/// </summary>
//	void SetCollosionAttribute(uint32_t collisionAttribute) { collisionAttribute_ = collisionAttribute; }
//
//#pragma endregion
//
//#pragma region CollisionMask
//
//	/// <summary>
//	/// CollisionMaskの取得
//	/// </summary>
//	uint32_t GetCollisionMask() const { return CollisionMask_; }
//
//	/// <summary>
//	/// CollisionMaskの設定
//	/// </summary>
//	void SetCollisionMask(uint32_t collisionMask) { CollisionMask_ = collisionMask; }
//
//#pragma endregion
//
//
//private:
//
//	AABB aabb_{};
//
//	uint32_t id_ = ObjectId::None;
//
//	uint32_t collisionAttribute_ = 0xffffffff;
//
//	uint32_t CollisionMask_ = 0xffffffff;
//
//	Vector3 size_ = { 1.0f, 1.0f ,1.0f };
//};



/* AABBColliderクラス */
class AABBCollider {

public:

	// 初期化処理
	void Init() {
		// 配置
		srt_;
		// サイズ
		size_ = Vector3::one;
		// 属性
		attribute_ = 0xffffffff;
		// マスク
		mask_ = 0xffffffff;
		// ID
		id_ = ObjectId::None;
	}

	// 衝突時コールバック関数
	void OnCollision(uint32_t id) {
		id;
	}


#pragma region Accessor

	// 配置
	SRTN GetSrt() const { return this->srt_; }
	void SetSrt(SRTN setSrt) { this->srt_ = setSrt; }

	// サイズ
	Vector3 GetSize() const { return this->size_; }
	void SetSize(Vector3 setSize) { this->size_ = setSize; }

	// 属性
	uint32_t GetAttribute() const { return this->attribute_; }
	void SetAttribute(uint32_t setAttribute) { this->attribute_ = setAttribute; }

	// マスク
	uint32_t GetMask() const { return this->mask_; }
	void SetMask(uint32_t setMask) { this->mask_ = setMask; }

	// ID
	uint32_t GetID() const { return this->id_; }
	void SetID(uint32_t setID) { this->id_ = setID; }

	// WorldPos
	Vector3 GetWorldPos() const {
		Matrix4x4 result = MakeAffineMatrix(srt_.scale, srt_.rotate, srt_.translate);
		return { result.m[3][0], result.m[3][1], result.m[3][2] };
	}

#pragma endregion 


private:

	// 配置
	SRTN srt_{};
	
	// サイズ
	Vector3 size_ = Vector3::one;

	// 属性
	uint32_t attribute_ = 0xffffffff;

	// マスク
	uint32_t mask_ = 0xffffffff;

	// ID
	uint32_t id_ = ObjectId::None;
};