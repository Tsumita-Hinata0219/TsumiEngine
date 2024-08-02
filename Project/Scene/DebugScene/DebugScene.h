#pragma once

#include "../../../Project/Scene/IScene.h"
#include "../../../Project/GameManager/GameManager.h"
#include "../../../Project/GameObject/GameObject.h"
#include "../../../Tsumi/3D/Model/ModelManager/ModelManager.h"
#include "../../../Tsumi/PipeLineManager/PipeLineManager.h"

#include "../../Project/GameObject/Camera/Manager/CameraManager.h"

#include "../../../Project/GameObject/Terrain/Skydome/Skydome.h"
#include "../../../Project/GameObject/Terrain/Skybox/Skybox.h"
#include "../../../Project/GameObject/Terrain/Ground/Ground.h"
#include "../../../Project/GameObject/Effect/TestPostEffect/TestPostEffect.h"
#include "../../../Project/GameObject/Others/TestHuman/TestHuman.h"
#include "../../../Project/GameObject/Others/TestJsonObject/TestJsonObject.h"
#include "../../../Project/GameObject/Others/TestBaseObject/TestBaseObject.h"


class DebugScene : public IScene {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	DebugScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~DebugScene();

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
	CameraManager* cameraManager_ = nullptr;
	CameraResource camera_;

	// Skydome
	std::unique_ptr<Skydome> skydome_;

	// Skybox
	std::unique_ptr<Skybox> skybox_;

	// Ground
	std::unique_ptr<Ground> ground_;

	// PostEffect
	std::unique_ptr<TestPostEffect> testPostEffect_;

	// TestHuman
	std::unique_ptr<TestHuman> testHuman_;

	// TestJsonObject
	std::unique_ptr<TestJsonObject> testJsonObject_;
};

