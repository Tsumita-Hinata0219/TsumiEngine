#pragma once

#include "Math/MyMath.h"
#include "Actor/Interface/IActor.h"


/* Actor クラスに対して機能を追加するためのモジュール */
class IComponent {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	IComponent(std::weak_ptr<IActor> owner, int updateOrder = 100);
	IComponent(IComponent& component);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~IComponent();

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update(float deltaTime);

	/// <summary>
	/// 更新順の取得
	/// </summary>
	int GetUpdateOrder() const { return this->updateOrder; }


protected:

	// Componentを持つ親Actor
	std::weak_ptr<IActor> owner;

	// 更新順
	int updateOrder;

};


template <class T, class... Types>
std::weak_ptr<IComponent> CreateComponent(std::weak_ptr<IActor> actor, Types... values)
{
	std::shared_ptr<IComponent> component;
	if (auto pActor = actor.lock()) {
		component = std::make_shared<T>(actor, values...);
		pActor->AddComponent(component);
	}
	return component;
}