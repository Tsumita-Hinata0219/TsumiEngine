#pragma once

#include "GameObject/IObject/IObject.h"


/* エネミーのシールド */
class EnemyShield : public IObject {
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyShield() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyShield() = default;

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

	/// <summary>
	/// バリアが壊れた時の処理
	/// </summary>
	void OnBarrierBroken();


private:

	/// <summary>
	/// DrawImGuiの描画
	/// </summary>
	void DrawImGui();
	
private:

	// モデル
	std::unique_ptr<Model> model_;

	// カラー　
	Vector4 color_{};

	// uvTransform
	Transform uvTrans_{};

	// トランスフォーム
	Transform trans_{};

	// コライダー
	std::unique_ptr<SphereCollider> sphere_;

};

