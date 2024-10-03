#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cmath>
#include <numbers>


#include "json.hpp"

#include "../3D/Model/ModelManager/ModelManager.h"

#include "../../Project/Math/MyMath.h"
#include "../../Project/GameObject/GameObject.h"



struct ColliderData {
	std::string type;
	Vector3 center;
	Vector3 size;
};
struct LevelData {

	struct ObjectData {
		std::string type;
		std::string file_name;
		SRT srt;
		std::map<std::string, std::unique_ptr<ObjectData>> children;
	};
	std::map<std::string, std::unique_ptr<ObjectData>> objects;
};
struct LevelObject {
	std::unique_ptr<Model> model;
	WorldTransform transform;
};


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
	void ScanningObjects(const std::string& path, nlohmann::json& object, std::map<std::string, std::unique_ptr<LevelData::ObjectData>>& objects);

	// 読み込んだ情報からモデル作成
	void CreateModel();


private: // メンバ変数

	// モデルマネージャー
	ModelManager* modelManager_ = nullptr;

	// Jsonファイルから読み込んだ情報をまとめておく変数
	std::unique_ptr<LevelData> levelData_;

	// 配置するための変数
	std::map<const std::string, std::list<std::unique_ptr<LevelObject>>> levelObjectMap_;

	// 読み込んだ情報をまとめておくコンテナ
	std::map<const std::string, SRTN> srtMap_;

};

