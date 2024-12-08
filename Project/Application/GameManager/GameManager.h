#pragma once

#include <chrono>

#include "Tsumi.h"
#include "Scene/IScene.h"
#include "Scene/DebugScene/DebugScene.h"

#include "Scene/TitleScene/TitleScene.h"
#include "Scene/SelectScene/SelectScene.h"
#include "Scene/GameScene/GameScene.h"
#include "Scene/ResultScene/ResultScene.h"

#include "GameData/GameData.h"

#include "Utilities/TextLog/TextLog.h"

#include <array>
#include <string>


// グローバル変数の定義
extern float g_ElapsedTime;


/* GameManagerクラス */
class GameManager {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameManager(IScene* newScene);

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
	void ChangeSceneState(IScene* newScene);


public:

	// シーンをまたいで使用したい値を保存しておくクラス
	std::unique_ptr<GameData> gameData_;


private:

	IScene* Scene_ = nullptr;

	std::chrono::steady_clock::time_point startTime_;

};