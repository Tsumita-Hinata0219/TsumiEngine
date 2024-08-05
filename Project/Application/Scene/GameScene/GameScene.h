#pragma once

#include "Scene/IScene.h"
#include "GameManager/GameManager.h"
#include "GameObject/GameObject.h"
#include "Model/ModelManager/ModelManager.h"
#include "PipeLineManager/PipeLineManager.h"
#include "JsonManager/JsonManager.h"

#include "GameObject/Camera/Manager/CameraManager.h"

#include "GameObject/Terrain/Skydome/Skydome.h"
#include "GameObject/Terrain/Skybox/Skybox.h"
#include "GameObject/Terrain/Ground/Ground.h"

#include "GameObject/Terrain/Wall/Wall.h"
#include "GameObject/Terrain/Floor/Floor.h"
#include "GameObject/Terrain/Building1/Building1.h"

#include "GameObject/Character/Player/Player.h"
#include "GameObject/Character/EnemyManager/EnemyManager.h"
#include "GameObject/Character/EnemyManager/Enemy/Enemy.h"

#include "PostEffect/IPostEffect/Absent/AbsentEffect.h"
#include "../../GameObject/Effect/TestPostEffect/TestPostEffect.h"


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

	// 衝突判定処理
	void CheckAllCollision();


private:

	// JsonFileManager
	JsonManager* jsonManager_ = nullptr;

	// CollisionManager
	//std::unique_ptr<CollisionManager> collisionManager_;

	// AbsentEffect
	std::unique_ptr<AbsentEffect> absentEffect_;

	// Skydome
	std::unique_ptr<Skydome> skydome_;

	// Ground
	std::unique_ptr<Ground> ground_;

	// Wall
	std::unique_ptr<Wall> wall_;

	// Floor
	std::unique_ptr<Floor> floor_;

	// Building1
	std::unique_ptr<Building1> building1_;

	// Player
	std::unique_ptr<Player> player_;

	// EnemyManager
	std::unique_ptr<EnemyManager> enemyManager_;

	// Enemy
	std::unique_ptr<Enemy> enemy_;
};

