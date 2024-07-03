#pragma once

#include "../../../Project/Scene/IScene.h"
#include "../../../Project/GameManager/GameManager.h"
#include "../../../Project/GameObject/GameObject.h"
#include "../../../Tsumi/3D/Model/ModelManager/ModelManager.h"
#include "../../../Tsumi/PipeLineManager/PipeLineManager.h"

#include "../../../Project/GameObject/Terrain/Skydome/Skydome.h"
#include "../../../Project/GameObject/Terrain/Ground/Ground.h"
#include "../../../Tsumi/PostEffect/PostEffect.h"
#include "../../../Project/GameObject/Effect/TestPostEffect/TestPostEffect.h"
#include "../../../Project/GameObject/Others/TestObject/TestObject.h"
#include "../../../Project/GameObject/Others/TestAnimationCube/TestAnimationCube.h"
#include "../../../Project/GameObject/Others/TestHuman/TestHuman.h"
#include "../../../Project/GameObject/Others/TestJsonObject/TestJsonObject.h"

#include "../../../Project/GameObject/Character/Player/Player.h"
#include "../../../Project/GameObject/Character/EnemyManager/Enemy/Enemy.h"



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

	// CollisionManager
	std::unique_ptr<CollisionManager> collisionManager_;

	// メインカメラ
	std::unique_ptr<Camera> camera_ = nullptr;

	// PostEffect
	std::unique_ptr<TestPostEffect> testPostEffect_;

	// TestModel
	std::unique_ptr<TestObject> testObject_;

	// TestAnimation
	std::unique_ptr<TestAnimationCube> testAnimCube_;

	// TestHuman
	std::unique_ptr<TestHuman> testHuman_;

	// TestJsonObject
	std::unique_ptr<TestJsonObject> testJsonObject_;

	Transform transform_;

	// Player
	std::unique_ptr<Player> player_;

	// Enemy
	std::unique_ptr<Enemy> enemy_;
};

