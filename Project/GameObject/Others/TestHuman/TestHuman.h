#pragma once

#include "../../GameObject.h"

/* TestHumanクラス */
class TestHuman {

public: 

	// コンストラクタ、デストラクタ	
	TestHuman() {};
	~TestHuman() {};

	// 初期化処理、更新処理、描画処理
	void Init();
	void Update();
	void Draw(Camera* camera);

private:

	//  ヒューマンモデル
	unique_ptr<Model> humanModel_;
	WorldTransform humanWt_{};
	float animTimeA_ = 0.0f;
	Skeleton humanSkeleton_{};
	SkinCluster humanSkinCluster_{};

	//  シンプルモデル
	unique_ptr<Model> simpleModel_;
	WorldTransform simpleWt_{};
	float animTimeB_ = 0.0f;
	Skeleton simpleSkeleton_{};
	SkinCluster simpleSkinCluster_{};

	// アニメーションタイプ
	Animation walkAnim_{};
	Animation simpleAnim_{};
};

