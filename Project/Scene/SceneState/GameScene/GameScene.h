#pragma once

#include "IScene.h"
#include "GameManager.h"
#include "GameObject.h"
#include "ModelManager.h"
#include "FileManager.h"

#include "Skydome/Skydome.h"
#include "Ground/Ground.h"
#include "PostEffect/PostEffect.h"
#include "TestObject/TestObject.h"
#include "TestAnimationCube/TestAnimationCube.h"
#include "TestHuman/TestHuman.h"


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
	unique_ptr<PostEffect> postEffect_;

	// TestModel
	unique_ptr<TestObject> testObject_;

	// TestAnimation
	unique_ptr<TestAnimationCube> testAnimCube_;

	// TestHuman
	unique_ptr<TestHuman> testHuman_;

	Transform transform_;
};
