#pragma once

#include "Entity/Actor/Interface/IActor.h"
#include "3D/Model/Model.h"
#include "Render/State/RenderState .h"


/* 描画用のコンポーネント */
class IRenderComponent {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	IRenderComponent(std::weak_ptr<IActor> owner);

	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~IRenderComponent() = default;

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw();


protected:

	// Componentを持つ親Actor
	std::weak_ptr<IActor> owner_;

	// モデル
	std::unique_ptr<Model> model_;

	// レンダーステート
	std::unique_ptr<RenderSystem::RenderState> renderState_;

};