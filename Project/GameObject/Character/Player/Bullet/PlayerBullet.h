#pragma once

#include "GameObject.h"


/* PlayerBullet */
class PlayerBullet {

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerBullet() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerBullet() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(Model& modelHD, Vector3 pos, Vector3 vel);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ViewProjection view);


private: // メンバ関数

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();


private: // メンバ変数

	// モデル
	std::unique_ptr<Model> model_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform worldTransform_{};

	// 加算速度
	Vector3 velocity_{};

	// 移動量
	Vector3 move_{};
};

