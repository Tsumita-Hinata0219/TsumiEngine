#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cmath>
#include <numbers>


#include "json.hpp"

#include "../FileManager/FileManager.h"

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
	void LoadSceneFile(const std::string& path, const std::string& fileName);


#pragma region Accessor アクセッサ


	LevelData::ObjectData* GetObjectData(const std::string& key) const {

		if (!levelData_) {
			return nullptr;
		}

		auto it = levelData_->objects.find(key);
		if (it != levelData_->objects.end()) {
			return it->second.get();
		}

		return nullptr;
	}

	SRT GetObjectSRT(const std::string& key) const {

		auto it = levelData_->objects.find(key);
		if (it != levelData_->objects.end()) {
			return it->second.get()->srt;
		}

		return SRT();
	}

#pragma endregion 


private:

	// オブジェクトの走査
	void ScanningObjects(nlohmann::json& object, std::map<std::string, std::unique_ptr<LevelData::ObjectData>>& objects);

	// 読み込んだ情報からモデル作成
	void CreateModel();


private: // メンバ変数

	// Jsonファイルから読み込んだ情報をまとめておく変数
	std::unique_ptr<LevelData> levelData_;

	// 配置するための変数
	std::map<const std::string, std::list<std::unique_ptr<LevelObject>>> levelObjectMap_;

	// 読み込んだ情報をまとめておくコンテナ
	std::map<const std::string, SRTN> srtMap_;
};

