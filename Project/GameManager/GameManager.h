#pragma once

#include "../../Tsumi/Tsumi.h"
#include "../Scene/IScene.h"
#include "../Scene/DebugScene/DebugScene.h"
#include "../Scene/GameScene/GameScene.h"
#include "../../Tsumi/Utilities/TextLog/TextLog.h"


/* GameManagerクラス */
class GameManager {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameManager();

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

private:

	IScene* Scene_ = nullptr;
};