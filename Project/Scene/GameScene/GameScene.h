#pragma once

#include "../../../Project/Scene/IScene.h"
#include "../../../Project/GameManager/GameManager.h"
#include "../../Tsumi/JsonManager/JsonManager.h"

#include "../../Project/GameObject/Camera/Manager/CameraManager.h"

#include "../../../Project/GameObject/Terrain/Skydome/Skydome.h"
#include "../../../Project/GameObject/Terrain/Skybox/Skybox.h"
#include "../../../Project/GameObject/Terrain/Ground/Ground.h"

#include "../../../Project/GameObject/Terrain/Wall/Wall.h"
#include "../../../Project/GameObject/Terrain/Floor/Floor.h"
#include "../../../Project/GameObject/Terrain/Building1/Building1.h"

#include "../../../Project/GameObject/Character/Player/Player.h"
#include "../../../Project/GameObject/Character/EnemyManager/EnemyManager.h"

#include "../../../Project/GameObject/Others/UI/Game/GameSceneUI.h"

#include "../../Tsumi/PostEffect/IPostEffect/Absent/AbsentEffect.h"
#include "../../GameObject/Effect/TestPostEffect/TestPostEffect.h"

#include "../../Tsumi/CollisionSystem/System/CollisionSystem.h"


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
	bool SceneChangeCheck(GameManager* state);

	// 衝突判定処理
	void CheckAllCollision();


private: // クラス

	// CollisionManager
	//std::unique_ptr<CollisionManager> collisionManager_;
	std::unique_ptr<CollisionSystem> collisionSystem_;

	// AbsentEffect
	std::unique_ptr<AbsentEffect> absentEffect_;

	// GameSceneUI
	std::unique_ptr<GameSceneUI> gameSceneUI_;

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


private:

	// シーンチェンジにかかる時間
	Timer sceneChange_;
};

