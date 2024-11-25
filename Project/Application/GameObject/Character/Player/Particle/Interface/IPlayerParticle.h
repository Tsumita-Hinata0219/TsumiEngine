#pragma once

#include <list>
#include <memory>

#include "GameObject/IObject/IObject.h"
#include "GameObject/GameObject.h"


/* PlayerのParticleの基底クラス */
class IPlayerParticle {

public:

	/// <summary>
	/// 仮想デストラク
	/// </summary>
	~IPlayerParticle() = default;

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


protected:

	// モデル
	std::unique_ptr<Model> model_;

	// トランスフォーム
	Transform trans_{};



};