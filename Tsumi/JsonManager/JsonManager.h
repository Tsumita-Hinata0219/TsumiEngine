#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cmath>
#include <numbers>


#include "json.hpp"
#include "../../Project/Math/MyMath.h"
#include "../../Project/GameObject/GameObject.h"


/* JsonManagerクラス */
class JsonManager {

private: // シングルトンデザインパターン

	// コンストラクタ、デストラクタ
	JsonManager() = default;
	~JsonManager() = default;
	JsonManager(const JsonManager&) = delete;
	const JsonManager& operator=(const JsonManager&) = delete;


public: // メンバ関数

	// インスタンスの取得
	static JsonManager* GetInstance() {
		static JsonManager instance;
		return &instance;
	}

	// 初期化処理、解放処理
	void Initialize();
	void Finalize();

	// Jsonファイルの読み込み
	void LoadJsonFile(const std::string& path, const std::string& fileName);


#pragma region Accessor アクセッサ


#pragma endregion 


private:



private: // メンバ変数



};

