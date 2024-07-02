#pragma once

#include <list>
#include <memory>

#include "../../../GameObject.h"


// Player前方宣言
class Player;


/* Enemyクラス */
class Enemy {

public: // メンバ関数

	// コンストラクタとデストラクタ
	Enemy() {};
	~Enemy() {};

	// 初期化処理　更新処理　描画処理
	void Initialize();
	void Update();
	void Draw3D(Camera* camera);

#pragma region Accessor アクセッサ

	// Playerの設定
	void SetPlayer(Player* setPlayer) { this->player_ = setPlayer; }


#pragma endregion 


private:

	// 移動処理
	void Move();

	// Velocityの計算処理
	void CalcVelocity();

	// 向きの計算処理
	void CalcRotate();

	// 射撃の処理
	void ExecuteShot();


private: // メンバ変数

	// Player
	Player* player_ = nullptr;

	// 本体モデル
	unique_ptr<Model> bodyModel_;

	// 本体座標
	WorldTransform bodyWt_{};

	// 移動速度
	Vector3 velocity_{};
	float moveVector_ = 0.05f;

	// playerとの最低距離
	float minToPlayer_ = 8.0f;

};

