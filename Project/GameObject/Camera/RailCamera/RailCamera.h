#pragma once

#include "GameObject.h"

/* RailCameraクラス */
class RailCamera {

public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(Vector3 rotate, Vector3 translate);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// ワールド変換データを取得
	/// </summary>
	WorldTransform& GetWorldTransform() { return worldTransform_; };

	/// <summary>
	/// ビュープロジェクションの取得関数
	/// </summary>
	ViewProjection& GetViewProjection() { return viewProjection_; }

private:

	// ワールドトランスフォーム
	WorldTransform worldTransform_{};

	// ビュープロジェクション
	ViewProjection viewProjection_{};
};

