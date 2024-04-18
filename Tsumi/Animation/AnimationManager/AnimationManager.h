#pragma once

#include "GameObject.h"
#include "AnimationDataArray.h"
#include "KeyFrameAnimation.h"

/* AnimationManagerクラス */
class AnimationManager {

public: // メンバ関数

	// コンストラクタ、デストラクタ
	AnimationManager() {};
	~AnimationManager() {};

	// 初期化処理、更新処理
	void Initialize();
	void Update();

private: // メンバ関数

	// Animationを読み込む
	Animation LoadAnimationFile(const std::string& routeFilePath, const std::string& fileName);


private: // メンバ変数

};

