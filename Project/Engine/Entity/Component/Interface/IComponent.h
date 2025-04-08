#pragma once

#include "Math/MyMath.h"
#include "../../Actor/Interface/IActor.h"


/* Actor クラスに対して機能を追加するためのモジュール */
class IComponent {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	IComponent();

	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~IComponent() = default;


	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Init() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update(float deltaTime);


#pragma region Accessor 

	// 名前
	std::string Get_Name() const { return name_; }

	// Owner
	void SetOwner(std::weak_ptr<IActor> setOwner) { owner_ = setOwner; }

#pragma endregion 


protected:

	// Componentを持つ親Actor
	std::weak_ptr<IActor> owner_;

	// Componentの名前
	std::string name_;

};
