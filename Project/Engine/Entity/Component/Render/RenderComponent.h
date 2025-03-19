#pragma once

#include "Entity/Actor/Interface/IActor.h"
#include "3D/Model/Model.h"


/* 描画用のコンポーネント */
class IRenderComponent {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	IRenderComponent();

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
	std::weak_ptr<IActor> owner;

	// モデル
	std::unique_ptr<Model> model_;

};