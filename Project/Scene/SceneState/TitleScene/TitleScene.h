#pragma once

#include "IScene.h"
#include "GameManager.h"

#include "GameObject.h"

#include "FadeManager.h"
#include "Skydome/Skydome.h"
#include "Ground/Ground.h"



class TitleScene : public IScene {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TitleScene() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleScene() {};

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

	bool funcFade_ = false;

	unique_ptr<Sprite> sprite_ = nullptr;
	SpriteTransform st_{};
	uint32_t texHD_;


	// ジョイコン
	XINPUT_STATE joyState_{};

	/* ----- Skydome スカイドーム ----- */
	std::unique_ptr<Skydome> skydome_ = nullptr;


	/* ----- Ground グラウンド ----- */
	std::unique_ptr<Ground> ground_ = nullptr;

};
