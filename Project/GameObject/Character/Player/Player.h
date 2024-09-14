#pragma once

#include <list>
#include <memory>

#include "../../IObject/IObject.h"
#include "../../GameObject.h"

#include "Boby/IPlayerBody.h"
#include "Boby/Main/PlayerMainBody.h"
#include "Boby/Left/PlayerLeftBody.h"
#include "Boby/Right/PlayerRightBody.h"

#include "Bullet/PlayerBullet.h"

#include "UI/PlayerUI.h"


// 前方宣言
class FollowCamera;


/* Playerクラス */
class Player : public IObject {

public: // メンバ関数

	// コンストラクタとデストラクタ
	Player() { attribute_ = ObjAttribute::PLAYER; }
	~Player() {};

	// 初期化処理　更新処理　描画処理
	void Init() override;
	void Update() override;
	void Draw3D() override;
	void Draw2DFront() override;
	void Draw2DBack() override;

	// 衝突判定コールバック関数
	void onCollision([[maybe_unused]] IObject* object) override;

#pragma region Accessor アクセッサ

	// フォローカメラ
	void SetFollowCamera(FollowCamera* camera) { this->followCamera_ = camera; }

	// WorldPos
	Vector3 GetWorldPos() { return this->trans_.GetWorldPos(); }

	// BulletList
	std::list<std::shared_ptr<PlayerBullet>>& GetBulletList() { return this->bulletList_; }

	// Collider
	//OBBCollider* GetOBBCollider() { return this->collider_.get(); }

	// KillCount
	uint32_t GetKillCount() const { return this->killCount_; }

	// KillCount加算 & 減算
	void AddKillCount(uint32_t addCount = 1) { this->killCount_ += addCount; }
	void SubKillCount(uint32_t subCount = 1) { this->killCount_ -= subCount; }

	// 死亡フラグ
	bool IsDead() const { return this->isDead_; }
	void SetDeadFlag(bool setFlag) { this->isDead_ = setFlag; }

	// HP
	uint32_t GetHP() const { return this->hp_; }
	void SetHP(uint32_t setHP) { this->hp_ = setHP; }

	// 勝敗のフラグ
	bool IsWin() const { return this->isWin_; }
	bool IsLose() const { return this->isLose_; }

#pragma endregion 

#pragma region Collision 衝突判定

	// 衝突自コールバック関数
	void OnCollisionWithEnemy();
	void OnCollisionWithEnemyBullet();

#pragma endregion 


private:

	// コライダーの更新
	void UpdateCollider();

	// 移動処理
	void Move();
	void KeyMove();
	void PadMove();

	// プレイヤー本体の姿勢処理
	void CalcBodyRotate();

	// 射撃処理
	void ExecuteShot();

	// 新しいバレットを生成する
	void CreateNewBullet();

	// バレットリストの追加
	void AddBulletList(std::shared_ptr<PlayerBullet> addBullet) { this->bulletList_.push_back(addBullet); }

	//// カメラ操作
	//void CameraOperation();

	//// カメラの回転処理
	//void CameraRotate();

	//// カメラのフォロー処理
	//void CameraFollow();

private: // メンバ変数

	// Inputクラス
	Input* input_ = nullptr;

	// フォローカメラ
	FollowCamera* followCamera_ = nullptr;

	//// カメラマネージャー
	//CameraManager* cameraManager_ = nullptr;

	// UI
	std::unique_ptr<PlayerUI> ui_;

	//// カメラ本体
	//CameraResource camera_{};

	// モデル
	// Body
	std::vector<std::shared_ptr<IPlayerBody>> iBodys_;

	// トランスフォーム
	Transform trans_{};

	// サイズ
	Vector3 size_ = { 2.0f, 2.0f, 2.0f };

	// 移動速度
	Vector3 velocity_{};
	float moveSpeed_ = 0.3f;
	float kBulletSpeed_ = 0.5f;

	// 死亡フラグ
	bool isDead_ = false;

	// コライダー
	//std::unique_ptr<OBBCollider> collider_;
	Col::Sphere sphere_;


	// HP
	uint32_t hp_ = 0;

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
	const float kAngleSpeed_ = 0.05f;

	// プレイヤーからのオフセット
	Vector3 cameraOffset_{};

	// プレイヤーのY軸姿勢制御値
	float playerRad_ = 0.0f;

	// キルカウント
	uint32_t killCount_ = 0;

	// ゲームに勝利したかのフラグ
	bool isWin_ = false;
	bool isLose_ = false;

};

