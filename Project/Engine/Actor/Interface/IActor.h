#pragma once

#include "Math/MyMath.h"
#include "Transform/Transform.h"
#include "Scene/IScene.h"


/* ゲーム内オブジェクトの基底クラス */
class IActor
{
public:

	// 状態
	enum class State {
		Active,
		Paused,
		Dead,
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	IActor();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~IActor();

	/// <summary>
	/// 更新処理関係
	/// </summary>
	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);


private:

	// 状態
	State m_State_;

	// Transform
	Transform transform_{};

	// 親シーン
	IScene* pScene_ = nullptr;

};