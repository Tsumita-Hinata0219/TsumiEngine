#pragma once

#include "../Interface/ICollider.h"


/* Sphereコライダークラス */
class SphereCollider : public ICollider {

public:

	/// <summary>
	/// パラメータ付きコンストラクタ
	/// </summary>
	SphereCollider(IObject* setOwner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SphereCollider() = default;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override {};

	/// <summary>
	/// ImGuiの描画
	/// </summary>
	void DrawImGui(const std::string& label = "") override;


#pragma region Accessor アクセッサ

	// Collider
	const Sphere& GetData() const { return this->data_; }
	void SetData(const Collider::ColliderData& setData) override { 
		if (const auto* data = dynamic_cast<const Sphere*> (&setData)) {
			this->data_ = (*data);
		}
	}

#pragma endregion 

	// コライダーのデータ
	Sphere data_{};
};
