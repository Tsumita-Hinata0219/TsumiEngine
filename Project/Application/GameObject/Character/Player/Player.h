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

public:

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
	//void UpdateCollider();

	// 入力を受け取る
	void InputFunc();

	// プレイヤーの移動
	void MoveFunc();

	// 移動方向を求める
	void CalcMoveDirection();

	// 移動処理
	void PadMove();
	void KeyMove();

	// 移動限界処理
	void MoveLimited();

	// カメラの方向に体の向きを合わせる
	void FaceCameraDirection();

	// 移動方向からY軸の姿勢を合わせる
	void CalcBodyOrienation(Vector2 input, Vector3 direction);

	// 射撃処理
	void ExecuteShot();

	// 新しいバレットを生成する
	void CreateNewBullet();

	// バレットリストの追加
	void AddBulletList(std::shared_ptr<PlayerBullet> addBullet) { this->bulletList_.push_back(addBullet); }

	// ImGuiの描画
	void DrawImGui();

private:

	// トランスフォーム
	Transform trans_{};

	// Light
	DirectionalLightData light_;

	// コライダー
	//Col::Sphere sphere_1_;
	Col::Sphere sphere_2_;

	// サイズ
	Vector3 size_ = { 2.0f, 2.0f, 2.0f };

	// 移動方向
	Vector3 stickMoveDirection_{};
	Vector3 keyMoveDirection_{};
	// 移動量
	Vector3 velocity_{};
	// 移動速度
	float moveSpeed_ = 0.3f;

	// 姿勢計算の補間速度
	float orientationLerpSpeed_ = 0.1f;

	// 死亡フラグ
	bool isDead_ = false;

	// HP
	uint32_t hp_ = 0;

	// キルカウント
	uint32_t killCount_ = 0;

	// ゲームに勝利したかのフラグ
	bool isWin_ = false;
	bool isLose_ = false;

#pragma region System

	// Inputクラス
	Input* input_ = nullptr;

	// デッドゾーン
	const float DZone_ = 0.2f;

	//Stickの入力を取得
	Vector2 iLStick_{};

	// Keyの入力
	Vector2 iKeys_{};

#pragma endregion 


private: // ボディ関連

	// リスト
	std::vector<std::shared_ptr<IPlayerBody>> iBodys_;


private: // バレット関連

	// リスト
	std::list<std::shared_ptr<PlayerBullet>> bulletList_;

	// 射撃中かのフラグ
	bool isShooting_ = false;

	// バレットの速度
	float kBulletSpeed_ = 0.5f;

	// 射撃ボタン押下フレーム&インターバル
	int shotPressFrame_ = 0;
	int kShotInterval_ = 5;


private: // UI関連

	std::unique_ptr<PlayerUI> ui_;


private: // フォローカメラ関連

	FollowCamera* followCamera_ = nullptr;


};

