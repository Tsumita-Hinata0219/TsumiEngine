#pragma once

#include "Tsumi.h"
#include "Scene/IScene.h"
#include "Scene/DebugScene/DebugScene.h"

#include "Scene/TitleScene/TitleScene.h"
#include "Scene/SelectScene/SelectScene.h"
#include "Scene/GameScene/GameScene.h"

#include "GameData/GameData.h"

#include "Utilities/TextLog/TextLog.h"


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

	std::unique_ptr<IScene> scene_;

	std::chrono::steady_clock::time_point startTime_;

};