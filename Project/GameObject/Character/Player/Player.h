#pragma once

#include "GameObject.h"

#include "Player/Bullet/PlayerBullet.h"


// GameSceneの前方宣言
class GameScene;

/* Playerクラス */
class Player {

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ViewProjection view);


#pragma region Get


#pragma endregion

#pragma region Set

	/// <summary>
	/// GameSceneの設定
	/// </summary>
	void SetRegisterScene(GameScene* scene) { GameScene_ = scene; }

#pragma endregion


private: // メンバ関数

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// 射撃処理
	/// </summary>
	void Attack();


private: // メンバ関数

	/// <summary>
	/// バレットリストの登録
	/// </summary>
	void PushBackBulletList();


private: // メンバ変数

	// モデル
	std::unique_ptr<Model> model_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform worldTransform_{};

	// 加算速度
	Vector3 velocity_{};

	// 移動量
	Vector3 move_{};
	float moveSpeed_;

	// 移動限界
	const VHInfo vhInfo = { 12.5f, 1.5f, 14.5f, -14.5f };


private: //メンバ変数

	GameScene* GameScene_ = nullptr;

	// モデル
	std::unique_ptr<Model> modelBullet_ = nullptr;

	// 移動速度
	Vector3 bulletVelocity_ = Vector3::zero;


};

