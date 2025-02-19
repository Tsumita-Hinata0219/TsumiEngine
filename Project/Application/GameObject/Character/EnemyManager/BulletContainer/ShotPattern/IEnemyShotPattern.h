#pragma once

#include "GameObject/GameObject.h"


// 前方宣言
class EnemyBulletContainer;


/* エネミーの射撃処理クラスの基底クラス */
class IEnemyShotPattern {

public:

	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~IEnemyShotPattern() = default;

	/// <summary>
	/// 射撃処理
	/// </summary>
	virtual void Execute() = 0;

	
protected:

	// 親
	EnemyBulletContainer* owner_ = nullptr;

};