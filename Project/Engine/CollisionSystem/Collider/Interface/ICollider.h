#pragma once

#include "../Structure/ColliderStructure.h"
#include "../ColliderConfig.h"
#include <variant>


// 前方宣言
class IObject;
class CollisionManager;


/* コライダーの基底クラス */
class ICollider {

public:

	// variant型で構造体をまとめる
	using ColliderDataType =
		std::variant<
		Collider::Sphere,
		Collider::AABB,
		Collider::OBB,
		Collider::Segment,
		Collider::ColliderData,
		>;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ICollider();

	/// <summary>
	/// 仮想デストラク
	/// </summary>
	virtual ~ICollider();

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// コライダー無効化
	/// </summary>
	void Deactivate();

	/// <summary>
	/// 衝突判定
	/// </summary>
	virtual bool Intersects(const ICollider& other) = 0;

	/// <summary>
	/// ImGuiの描画
	/// </summary>
	virtual void DrawImGui(const std::string& label = "") = 0;


#pragma region Accessor アクセッサ

	// データ
	virtual ColliderDataType GetData() const = 0;
	virtual void SetData(const Collider::ColliderData& setData) = 0;

	// オーナー
	virtual IObject* getOwner() { return this->owner_; }

	// 属性
	virtual uint32_t GetAttribute() { return this->attribute_; }
	virtual void ColliderAttribute(uint32_t setAttribute) { this->attribute_ = setAttribute; }

	// アクティブ
	virtual bool IsActive() const { return this->isActive_; }

#pragma endregion 


protected:

	// マネージャ
	CollisionManager* manager_ = nullptr;

	// コライダーを持つオーナー
	IObject* owner_ = nullptr;

	// 属性
	uint32_t attribute_ = 0;

	// アクティブフラグ
	bool isActive_ = false;

};

