#pragma once

#include "GameObject/IObject/IObject.h"
#include "GameObject/GameObject.h"


// 前方宣言



/* エネミーのエフェクトの基底クラス */
class IEnemyEffect {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	IEnemyEffect() = default;

	/// <summary>
	/// 仮想デストラク
	/// </summary>
	virtual ~IEnemyEffect() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw3D() = 0;


#pragma region Accessor アクセッサ

	// 死亡フラグ
	bool IsDead() const { return this->isDead_; }

#pragma endregion 


private:

	// モデル
	std::unique_ptr<Model> model_;

	// トランスフォーム
	Transform trans_{};

	// 死亡フラグ
	bool isDead_ = false;

	// タイマー
	Timer timer_{};

};