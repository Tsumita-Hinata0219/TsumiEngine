#pragma once

#include <list>
#include <memory>

#include "../../IObject/IObject.h"
#include "../../GameObject.h"

#include "Bullet/PlayerBullet.h"


/* Playerクラス */
class Player : public IObject {

public: // メンバ関数

	// コンストラクタとデストラクタ
	Player() {};
	~Player() {};

	// 初期化処理　更新処理　描画処理
	void Init() override;
	void Update() override;
	void Draw3D() override;
	void Draw2DFront() override;
	void Draw2DBack() override;

#pragma region Accessor アクセッサ

	// WorldPos
	Vector3 GetWorldPos() { return this->trans_.GetWorldPos(); }

	// BulletList
	std::list<std::shared_ptr<PlayerBullet>>& GetBulletList() { return this->bulletList_; }

	// Collider
	OBBCollider* GetOBBCollider() { return this->collider_.get(); }

#pragma endregion 

#pragma region Collision 衝突判定

	// 衝突自コールバック関数
	void OnCollisionWithEnemy();
	void OnCollisionWithEnemyBullet();

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

	// カメラ操作
	void CameraOperation();

	// カメラの回転処理
	void CameraRotate();


private: // メンバ変数

	// Inputクラス
	Input* input_ = nullptr;

	// カメラマネージャー
	CameraManager* cameraManager_ = nullptr;

	// カメラ本体
	CameraResource camera_{};

	// モデル
	std::unique_ptr<Model> model_;

	// トランスフォーム
	Transform trans_{};

	// サイズ
	Vector3 size_ = { 2.0f, 2.0f, 2.0f };

	// 移動速度
	Vector3 velocity_{};
	float moveVector_ = 0.3f;
	float kBulletSpeed_ = 0.5f;

	// コライダー
	std::unique_ptr<OBBCollider> collider_;

	// BulletのList配列
	std::list<std::shared_ptr<PlayerBullet>> bulletList_;

	// 射撃ボタン押下フレーム&インターバル
	int shotPressFrame_ = 0;
	int kShotInterval_ = 5;

	//Stickの入力を取得
	Vector2 L_StickInput_{};
	Vector2 R_StickInput_{};

	// Light
	DirectionalLightData light_;

	// カメラの回転に使う変数
	float cameraAngle_ = 0.0f;
	const float kCameraRadius_ = 5.0f;
	const float kAngleSpeed_ = 2.0f;

	// プレイヤーからのオフセット
	Vector3 cameraOffset_{};
};

