#pragma once

#include "Math/MyMath.h"
#include "../../Actor/Interface/IActor.h"


/* Actor クラスに対して機能を追加するためのモジュール */
class IComponent {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	IComponent(std::weak_ptr<IActor> owner);

	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~IComponent() = default;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update(float deltaTime);


protected:

	// Componentを持つ親Actor
	std::weak_ptr<IActor> owner;

};
