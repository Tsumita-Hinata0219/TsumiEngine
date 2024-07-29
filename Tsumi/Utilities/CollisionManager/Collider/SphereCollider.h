#pragma once

#include<cstdint>

#include "../CollisionStructures/CollisionStructures.h"
#include "ColliderConfig.h"

#include "../../Project/Math/MyMath.h"
#include "../../../Transform/Transform.h"


/* SphereColliderクラス */
class SphereCollider {

public:

	// 初期化処理
	void Init() {
		// 配置
		srt_;
		// 半径
		radius_ = 1.0f;
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

	// 半径
	float GetRadius() const { return this->radius_; }
	void SetRadius(float setRadius) { this->radius_ = setRadius; }

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

	// 半径
	float radius_ = 0.0f;

	// 属性
	uint32_t attribute_ = 0xffffffff;

	// マスク
	uint32_t mask_ = 0xffffffff;

	// ID
	uint32_t id_ = ObjectId::None;
};