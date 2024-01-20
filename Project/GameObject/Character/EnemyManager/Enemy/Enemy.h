#pragma once

#include "GameObject.h"

#include "EnemyManager/MovePhase/IEnemyMovePhaseState.h"
#include "EnemyManager/MovePhase/Approach/IEnemyMoveApproachState.h"
#include "EnemyManager/MovePhase/Leave/IEnemyMoveLeaveState.h"


// Playerの前方宣言
class Player;

// GameSceneの前方宣言
class GameScene;

/* Enemyクラス */
class Enemy {

public: // メンバ関数

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
	void MoveApproach();
	void MoveLeave();


#pragma region Get

	/// <summary>
	/// ワールド座標の取得
	/// </summary>
	WorldTransform GetWorldTransform() { return this->worldTransform_; }

	/// <summary>
	/// Playerの取得
	/// </summary>
	Player* GetPlayer() { return this->player_; }

	/// <summary>
	/// 死亡フラグの取得
	/// </summary>
	bool IsDead() { return this->isDead_; }

#pragma endregion 

#pragma region Set

	/// <summary>
	/// Playerの設定
	/// </summary>
	void SetPlayer(Player* player) { this->player_ = player; }

	/// <summary>
	/// 死亡フラグの設定
	/// </summary>
	void SetIsDead(bool flag) { this->isDead_ = flag; }

#pragma endregion 


private: // メンバ関数


private: // メンバ変数

	// 登録先シーン
	GameScene* GameScene_ = nullptr;

	// プレイヤー
	Player* player_ = nullptr;

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


public: // メンバ関数

#pragma region Get

	/// <summary>
	/// ムーブフェーズの取得
	/// </summary>
	int GetMovePhaseNum() { return this->movePhaseNum_; }

#pragma endregion 

#pragma region Set

	/// <summary>
	/// ムーブフェーズの設定
	/// </summary>
	void SetMovePhaseNun(int nextPhase) { this->movePhaseNum_ = nextPhase; }

#pragma endregion 


private: // メンバ関数

	/// <summary>
	/// ムーブフェーズの初期化処理
	/// </summary>
	void MovePhaseInit();

	/// <summary>
	/// ムーブフェーズの更新処理
	/// </summary>
	void MovePhaseUpdate();


private: // メンバ変数

	// ムーブフェーズ
	std::unique_ptr<IEnemyMovePhaseState> movePhaseArr_[2];
	int movePhaseNum_ = 0;
	int currMovePhase_;
	int prevMovePhase_;

};



