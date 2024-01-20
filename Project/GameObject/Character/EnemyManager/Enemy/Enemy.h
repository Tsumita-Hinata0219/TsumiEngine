#pragma once

#include "GameObject.h"


// GameSceneの前方宣言
class GameScene;

/* Enemyクラス */
class Enemy {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Enemy() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Enemy() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(Model& modelEnemy, Vector3 pos, Vector3 move);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ViewProjection view);

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();


#pragma region Get

	/// <summary>
	/// 死亡フラグの取得
	/// </summary>
	bool IsDead() { return this->isDead_; }

#pragma endregion 

#pragma region Set

	/// <summary>
	/// 死亡フラグの取得
	/// </summary>
	void SetIsDead(bool flag) { this->isDead_ = flag; }

#pragma endregion 


private:

	// 登録先シーン
	GameScene* GameScene_ = nullptr;

	// モデル
	unique_ptr<Model> model_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform worldTransform_{};

	// 加算速度
	Vector3 velocity_{};

	// 移動量
	Vector3 move_{};

	// 死亡フラグ
	bool isDead_ = false;
};



