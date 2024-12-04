#pragma once

#include "../Interface/ICollider.h"


namespace Collider {

	class SphereCollider : public ICollider	{

	public:

		/// <summary>
		/// コンストラクタ
		/// </summary>
		SphereCollider() = default;

		/// <summary>
		/// デストラクタ
		/// </summary>
		~SphereCollider() = default;

		/// <summary>
		/// 更新処理
		/// </summary>
		void Update() override {};


#pragma region Accessor アクセッサ

		// Collider
		const Sphere& GetData() { return this->sphere_; }
		void SetData(const Sphere& setData) { this->sphere_ = setData; }

#pragma endregion 


	private:

		Sphere sphere_{};

	};
}
