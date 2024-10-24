#pragma once

#include "Scene/IScene.h"
#include "GameManager/GameManager.h"
#include "GameObject/GameObject.h"

#include "GameObject/Others/SceneTransition/SceneTransition.h"


class ResultScene : public IScene {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ResultScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ResultScene();

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

	// ResultTexture
	uint32_t resultTexHD_{};
	WorldTransform resultWt_{};;
	std::unique_ptr<Sprite> resultSp_;

	// SceneTransition
	SceneTransition* sceneTransition_ = nullptr;
};

