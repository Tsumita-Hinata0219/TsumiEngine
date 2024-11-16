#pragma once

#include "Scene/IScene.h"
#include "GameManager/GameManager.h"
#include "JsonManager/JsonManager.h"
#include "CollisionSystem/System/CollisionSystem.h"
#include "CollisionSystem/Manager/CollisionManager.h"

#include "GameObject/Camera/Manager/CameraManager.h"
#include "GameObject/Camera/GameCamera/GameCamera.h"

#include "GameObject/Others/SceneTransition/SceneTransition.h"
#include "GameObject/Others/StartDirection/StartDirection.h"

#include "GameObject/Terrain/Skydome/Skydome.h"
#include "GameObject/Terrain/Skybox/Skybox.h"
#include "GameObject/Terrain/Ground/Ground.h"
#include "GameObject/Terrain/Wall/Wall.h"
#include "GameObject/Terrain/Floor/Floor.h"
#include "GameObject/Terrain/Building1/Building1.h"

#include "GameObject/Character/Player/Player.h"
#include "GameObject/Character/EnemyManager/EnemyManager.h"

#include "GameObject/Others/UI/Game/GameSceneUI.h"

#include "PostEffect/IPostEffect/Absent/AbsentEffect.h"
#include "GameObject/Effect/TestPostEffect/TestPostEffect.h"


class GameScene : public IScene {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

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

	// シーンチェンジチェック
	void SceneChangeCheck();


private: // クラス

	// CollisionManager
	CollisionManager* CollisionManager_ = nullptr; // シングルトン

	// AbsentEffect
	std::unique_ptr<AbsentEffect> absentEffect_;

	// PostEffect
	std::unique_ptr<TestPostEffect> testPostEffect_;

	// GameSceneUI
	std::unique_ptr<GameSceneUI> gameSceneUI_;

	// GameCamera
	std::unique_ptr<GameCamera> gameCamera_;

	// StartDirection
	std::unique_ptr<StartDirection> startDirection_;

	// Skybox
	std::unique_ptr<Skybox> skybox_;

	// Wall
	std::unique_ptr<Wall> wall_;

	// Floor
	std::unique_ptr<Floor> floor_;

	// Player
	std::unique_ptr<Player> player_;

	// EnemyManager
	std::unique_ptr<EnemyManager> enemyManager_;

	// SceneTransition
	SceneTransition* sceneTransition_ = nullptr;
};

