#pragma once

#include "Tsumi.h"
#include "Scene/IScene.h"
#include "Scene/DebugScene/DebugScene.h"

#include "Scene/TitleScene/TitleScene.h"
#include "Scene/SelectScene/SelectScene.h"
#include "Scene/GameScene/GameScene.h"

#include "GameData/GameData.h"

#include "Utilities/TextLog/TextLog.h"
#include "Utilities/TimeSystem/TimeSystem.h"

#include <array>
#include <string>
#include <memory>


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

	// 現在のシーン
	std::unique_ptr<IScene> scene_;

	std::chrono::steady_clock::time_point startTime_;

	std::unique_ptr<AbsentEffect> copyImage_;
};