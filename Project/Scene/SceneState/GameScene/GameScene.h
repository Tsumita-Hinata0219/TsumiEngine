#pragma once

#include "IScene.h"
#include "GameManager.h"

#include "GameObject.h"

#include "RailCamera/RailCamera.h"
#include "Skydome/Skydome.h"
#include "Ground/Ground.h"
#include "Player/Player.h"
#include "EnemyManager/EnemyManager.h"
#include "FadeManager.h"


class GameScene : public IScene {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameScene() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(GameManager* state) override;

	/// <summary>
	/// 背景スプライトの描画処理
	/// </summary>
	void BackSpriteDraw() override;

	/// <summary>
	/// ３Dオブジェクトの描画処理
	/// </summary>
	void ModelDraw() override;

	/// <summary>
	/// 前景スプライトの描画処理
	/// </summary>
	void FrontSpriteDraw() override;


public: // メンバ関数

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollision();

	/// <summary>
	/// プレイヤーバレットを追加する
	/// </summary>
	void AddPlayerBulletList(PlayerBullet* playerBullet) { playerBullets_.push_back(playerBullet); }

	/// <summary>
	/// エネミーを追加する
	/// </summary>
	void AddEnemyList(Enemy* enemy) { enemys_.push_back(enemy); }

	/// <summary>
	/// エネミーバレットを追加する
	/// </summary>
	void AddEnemyBulletList(EnemyBullet* enemyBullet) { enemyBullets_.push_back(enemyBullet); }

	
private:

	// メインカメラ
	ViewProjection GameCamera_{};

	/* ----- DebugCamera デバッグカメラ----- */
	std::unique_ptr<DebugCamera> debugCamera_ = nullptr;


	/* ----- RailCamera レールカメラ----- */
	std::unique_ptr<RailCamera> railCamera_ = nullptr;


	/* ----- CollisionManager コリジョンマネージャー ----- */
	std::unique_ptr<CollisionManager> collisionManager_ = nullptr;


	/* ----- Skydome スカイドーム ----- */
	std::unique_ptr<Skydome> skydome_ = nullptr;


	/* ----- Ground グラウンド ----- */
	std::unique_ptr<Ground> ground_ = nullptr;


	/* ----- Player プレイヤー ----- */
	std::unique_ptr<Player> player_ = nullptr;
	std::list<PlayerBullet*> playerBullets_{};


	/* ----- Enemy エネミー ----- */
	std::unique_ptr<EnemyManager> enemyManager_ = nullptr;
	std::list<Enemy*> enemys_{};
	std::list<EnemyBullet*> enemyBullets_{};

	// ジョイコン
	XINPUT_STATE joyState_{};
	bool funcFade_ = false;

	uint32_t timer_;
};

