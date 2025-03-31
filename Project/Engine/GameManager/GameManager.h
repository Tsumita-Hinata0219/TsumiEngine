#pragma once

#include <array>
#include <string>
#include <memory>

#include "Tsumi.h"
#include "Scene/IScene.h"
#include "Utilities/TextLog/TextLog.h"
#include "Utilities/TimeSystem/TimeSystem.h"
#include "GameData/GameData.h"
#include "Entity/Actor/Manager/ActorManager.h"
#include "Entity/TransformNode/Manager/TransformNodeManager.h"
#include "RenderSystem/Asset/RenderAssetManager.h"

#include "Scene/DebugScene/DebugScene.h"
#include "Scene/DevScene/DevScene.h"
#include "Scene/TitleScene/TitleScene.h"
#include "Scene/SelectScene/SelectScene.h"
#include "Scene/GameScene/GameScene.h"



// グローバル変数の定義
extern float g_ElapsedTime;


/* GameManagerクラス */
class GameManager {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameManager(std::unique_ptr<IScene> initScene);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameManager();

	/// <summary>
	/// ゲームループ
	/// </summary>
	void Run();

	/// <summary>
	/// シーンチェンジ
	/// </summary>
	void ChangeSceneState(std::unique_ptr<IScene> newScene);


private:

	// フレームワーク
	Tsumi* tsumi_ = nullptr;

	// DirectX
	DirectXManager* dxManager_ = nullptr;

	// 時間記録
	TimeSystem* timeSys_ = nullptr;

	// ActorManager
	ActorManager* actorManager_ = nullptr;

	// TransformNodeManager
	TransformNodeManager* transformNodeManager_ = nullptr;

	// RenderAssetManager
	RenderSystem::RenderAssetManager* renderAssetManager = nullptr;

	// 現在のシーン
	std::unique_ptr<IScene> scene_;
	std::chrono::steady_clock::time_point startTime_;
	std::unique_ptr<AbsentEffect> copyImage_;
};