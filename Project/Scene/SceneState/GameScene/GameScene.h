#pragma once

#include "IScene.h"
#include "GameManager.h"

#include "ViewProjection.h"

#include "Skydome/Skydome.h"
#include "Ground/Ground.h"
#include "Player/Player.h"
#include "Player/Bullet/PlayerBullet.h"


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
	/// プレイヤーバレットを追加する
	/// </summary>
	void AddPlayerBulletList(PlayerBullet* playerBullet) { playerBullets_.push_back(playerBullet); }

	
private:

	// メインカメラ
	ViewProjection GameCamera_{};


	/* ----- Skydome スカイドーム ----- */
	std::unique_ptr<Skydome> skydome_ = nullptr;


	/* ----- Ground グラウンド ----- */
	std::unique_ptr<Ground> ground_ = nullptr;


	/* ----- Player プレイヤー ----- */
	std::unique_ptr<Player> player_ = nullptr;
	std::list<PlayerBullet*> playerBullets_{};


};

