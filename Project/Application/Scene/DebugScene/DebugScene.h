#pragma once

#include "Scene/IScene.h"
#include "GameManager/GameManager.h"
#include "GameObject/GameObject.h"
#include "3D/Model/Manager/ModelManager.h"
#include "PipeLineManager/PipeLineManager.h"
#include "ConfigManager/ConfigManager.h"

#include "Camera/Manager/CameraManager.h"

#include "GameObject/Terrain/Skydome/Skydome.h"
#include "3D/Skybox/Skybox.h"
#include "GameObject/Effect/TestPostEffect/TestPostEffect.h"
#include "GameObject/Others/TestHuman/TestHuman.h"
#include "GameObject/Others/TestBaseObject/TestBaseObject.h"

#include "GameObject/Dev/DemoParticle/DemoParticle.h"


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
	void Update() override;

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

	// Skybox
	std::unique_ptr<Skybox> skybox_;

	// DemoParticle
	std::unique_ptr<DemoParticle> demoParticle_;
};

