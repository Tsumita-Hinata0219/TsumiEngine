#pragma once

#include "../../../Project/Scene/IScene.h"
#include "../../../Project/GameManager/GameManager.h"
#include "../../../Project/GameObject/GameObject.h"
#include "../../../Tsumi/Utilities/FadeManager/FadeManager.h"

#include "../../../Project/GameObject/Terrain/Skybox/Skybox.h"

#include "../../Project/GameObject/Terrain/TitleScreen/TitleScreen.h"

#include "../../Tsumi/PostEffect/IPostEffect/Absent/AbsentEffect.h"


#include "../../Tsumi/PostEffect/IPostEffect/Absent/AbsentEffect.h"


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

	// TitleScreen
	std::unique_ptr<TitleScreen> titleScreen_;

	// Skybox
	std::unique_ptr<Skybox> skybox_;

	// FadeManager
	FadeManager* fadeManager_ = nullptr;


private:

	// フェード処理のフラグ
	bool isFadeFunc_ = false;
};

