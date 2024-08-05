#pragma once

#include "../../GameObject.h"
#include "3D/Model/ModelManager/ModelManager.h"
#include "ConfigManager/ConfigManager.h"

/* TestHumanクラス */
class TestHuman {

public: 

	// コンストラクタ、デストラクタ	
	TestHuman() {};
	~TestHuman() {};

	// 初期化処理、更新処理、描画処理
	void Init();
	void Update();
	void Draw();

private:

	// モデルマネージャー
	ModelManager* modelManager_ = nullptr;

	// コンフィグマネージャー
	ConfigManager* configManager_ = nullptr;

	// ヒューマン
	std::unique_ptr<Model> humanModel_;
	Transform humanTrans_{};

	// ライト
	DirectionalLightData light_{};
	// 環境マップ
	EnvironmentData enviroment_{};
};

