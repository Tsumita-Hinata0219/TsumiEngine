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
	/// 生成
	/// </summary>
	virtual void Create() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() {};

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();


protected:

	// Componentを持つ親Actor
	std::weak_ptr<IActor> owner_;

	// レンダーステート
	std::unique_ptr<RenderSystem::RenderState> renderState_;

};