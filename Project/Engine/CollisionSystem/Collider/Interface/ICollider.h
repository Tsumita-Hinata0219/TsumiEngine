#pragma once

#include "../Structure/ColliderStructure.h"


// 前方宣言
class IObject;


namespace Collider {

	/* コライダーの基底クラス */
	class ICollider {

	public:

		/// <summary>
		/// 仮想デストラク
		/// </summary>
		virtual ~ICollider() = default;

		/// <summary>
		/// 更新処理
		/// </summary>
		virtual void Update() = 0;

		/// <summary>
		/// ImGuiの描画
		/// </summary>
		virtual void DrawImGui() = 0;


#pragma region Accessor アクセッサ

		// オーナー
		virtual IObject* getOwner() { return this->owner_; }

#pragma endregion 


	protected:

		// コライダーを持つオーナー
		IObject* owner_ = nullptr;

	};
}

