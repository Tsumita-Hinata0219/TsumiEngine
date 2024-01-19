#pragma once

#include "IScene.h"
#include "GameManager.h"

#include "ViewProjection.h"
#include "Player/Player.h"
#include "Skydome/Skydome.h"
#include "Ground/Ground.h"


class GameScene : public IScene {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameScene() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene() {};

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
	

private:

	// メインカメラ
	ViewProjection GameCamera_{};

	// プレイヤー
	std::unique_ptr<Player> player_ = nullptr;

	// スカイドーム
	std::unique_ptr<Skydome> skydome_ = nullptr;

	// グラウンド
	std::unique_ptr<Ground> ground_ = nullptr;
};

