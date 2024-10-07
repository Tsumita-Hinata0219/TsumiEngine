#pragma once

#include "Scene/IScene.h"
#include "GameManager/GameManager.h"
#include "GameObject/GameObject.h"
#include "Utilities/FadeManager/FadeManager.h"

#include "PostEffect/IPostEffect/Absent/AbsentEffect.h"
#include "GameObject/Effect/TestPostEffect/TestPostEffect.h"

#include "GameObject/Terrain/Skybox/Skybox.h"

#include "GameObject/Terrain/TitleScreen/TitleScreen.h"
#include "GameObject/Others/TitleBackGround/TitleBackGround.h"


class TitleScene : public IScene {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TitleScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleScene();

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

	// Input
	Input* input_ = nullptr;

	// カメラマネージャー
	CameraManager* cameraManager_ = nullptr;

	// カメラ本体
	CameraResource camera_{};

	// AbsentEffect
	std::unique_ptr<AbsentEffect> absentEffect_;

	// TestPostEffect
	std::unique_ptr<TestPostEffect> testPostEffect_;

	// TitleScreen
	std::unique_ptr<TitleScreen> titleScreen_;

	// TitleBackGround
	std::unique_ptr<TitleBackGround> titleBG_;

	// Skybox
	std::unique_ptr<Skybox> skybox_;

	// FadeManager
	FadeManager* fadeManager_ = nullptr;


private:

	// フェード処理のフラグ
	bool isFadeFunc_ = false;
};

