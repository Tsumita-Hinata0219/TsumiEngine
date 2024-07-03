#pragma once

#include <list>
#include <memory>

#include "../../GameObject.h"


/* EnemyManagerクラス */
class EnemyManager {

public: // メンバ関数

	// コンストラクタ、デストラクタ
	EnemyManager() {};
	~EnemyManager() {};

	// 初期化処理、更新処理、描画処理
	void Initialize();
	void Update();
	void Draw3D(Camera* camera);


private: // メンバ変数



};

