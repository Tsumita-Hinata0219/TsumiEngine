#pragma once

#include "GameObject.h"
#include "AnimationDataArray.h"
#include "KeyFrameAnimation.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


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

	// 同じファイルは読み込まない
	bool CheckAnimationFile(string fileName);

private: // メンバ変数

	map<string, unique_ptr<Animation>> animationDatas_{};
};

