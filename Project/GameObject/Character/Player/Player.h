#pragma once

#include <list>
#include <memory>

#include "../../GameObject.h"

#include "Bullet/PlayerBullet.h"


/* Playerクラス */
class Player {

public: // メンバ関数

	// コンストラクタとデストラクタ
	Player() {};
	~Player() {};

	// 初期化処理　更新処理　描画処理
	void Initialize();
	void Update();
	void Draw2DBack(Camera* camera);
	void Draw3D(Camera* camera);
	void Draw2DFront(Camera* camera);


#pragma region Accessor アクセッサ

	// 座標
	Vector3 GetPosition() { return this->bodyWt_.GetWorldPos(); }


#pragma endregion 


private:

	// 移動処理
	void Move();

	// プレイヤー本体の姿勢処理
	void CalcBodyRotate();

	// 射撃処理
	void ExecuteShot();

	// 新しいバレットを生成する
	void CreateNewBullet();

	// バレットリストの追加
	void AddBulletList(std::shared_ptr<PlayerBullet> addBullet) { this->bulletList_.push_back(addBullet); }


private: // メンバ変数

	// Inputクラス
	Input* input_ = nullptr;

	// 本体モデル
	unique_ptr<Model> bodyModel_;

	// 本体座標
	WorldTransform bodyWt_{};

	// 移動速度
	Vector3 velocity_{};
	float moveVector_ = 0.3f;
	float kBulletSpeed_ = 0.5f;

	// BulletのList配列
	std::list<std::shared_ptr<PlayerBullet>> bulletList_;

	// 射撃ボタン押下フレーム&インターバル
	int shotPressFrame_ = 0;
	int kShotInterval_ = 10;

};

