#pragma once

#include "../Project/Scene/IScene.h"
#include "../Project/GameManager/GameManager.h"
#include "../Project/GameObject/GameObject.h"
#include "Model/ModelManager/ModelManager.h"

#include "../Project/GameObject/Terrain/Skydome/Skydome.h"
#include "../Project/GameObject/Terrain/Ground/Ground.h"
#include "PostEffect/PostEffect.h"
#include "../Project/GameObject/Effect/TestPostEffect/TestPostEffect.h"
#include "../Project/GameObject/Others/TestObject/TestObject.h"
#include "../Project/GameObject/Others/TestAnimationCube/TestAnimationCube.h"
#include "../Project/GameObject/Others/TestHuman/TestHuman.h"
#include "../Project/GameObject/Others/TestJsonObject/TestJsonObject.h"


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

	// メインカメラ
	unique_ptr<Camera> camera_ = nullptr;

	// PostEffect
	unique_ptr<TestPostEffect> testPostEffect_;

	// TestModel
	unique_ptr<TestObject> testObject_;

	// TestAnimation
	unique_ptr<TestAnimationCube> testAnimCube_;

	// TestHuman
	unique_ptr<TestHuman> testHuman_;

	// TestJsonObject
	unique_ptr<TestJsonObject> testJsonObject_;

	Transform transform_;
};
