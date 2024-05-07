#pragma once

#include "IScene.h"
#include "GameManager.h"
#include "GameObject.h"

#include "Skydome/Skydome.h"
#include "Ground/Ground.h"
#include "PostEffect/PostEffect.h"


class GameScene : public IScene {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameScene();

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


private:

	// メインカメラ
	unique_ptr<Camera> camera_ = nullptr;

	// PostEffect
	unique_ptr<PostEffect> postEffect_;


	unique_ptr<Sprite> sp_;
	//uint32_t tex_;
	WorldTransform wt_;
};
