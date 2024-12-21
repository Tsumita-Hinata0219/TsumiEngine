#pragma once

#include "GameObject/IObject/IObject.h"


/* エネミーのシールド */
class EnemyShield : public IObject {
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyShield();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyShield();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Draw3D() override;
	void Draw2DFront() override;
	void Draw2DBack() override;

	/// <summary>
	/// 衝突判定コールバック関数
	/// </summary>
	void onCollision([[maybe_unused]] IObject* object) override;
	
private:

	// モデル
	std::unique_ptr<Model> model_;

	// トランスフォーム
	Transform trans_{};

};

