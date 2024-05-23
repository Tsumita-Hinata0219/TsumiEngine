#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cassert>

#include "json.hpp"
#include"MyMath.h"


struct ColliderData {
	std::string type;
	Vector3 center;
	Vector3 size;
};
struct LevelData {
	
	struct ObjectData {
		std::string type;
		std::string file_name;
		Vector3 translation;
		Vector3 rotation;
		Vector3 scaling;
		std::map<std::string, std::unique_ptr<ObjectData>> children;
	};
	std::map<std::string, std::unique_ptr<ObjectData>> objects;
};


/* FileManagerクラス */
class FileManager {

private:

	// コンストラクタ、デストラクタ
	FileManager() = default;
	~FileManager() = default;
	FileManager(const FileManager&) = delete;
	const FileManager& operator=(const FileManager&) = delete;

public:

	// インスタンスの取得
	static FileManager* GetInstance() {
		static FileManager instance;
		return&instance;
	}

	// 初期化処理
	void Initialize();

	// 解放処理
	void Finalize();

	// JSONファイル読み込み
	void LoadJsonFile(const std::string& routeFilePath, const std::string& fileName);


#pragma region Get

	LevelData::ObjectData* GetObjectData(const std::string& key) const  {

		if (!levelData_) {
			return nullptr;
		}

		auto it = levelData_->objects.find(key);
		if (it != levelData_->objects.end()) {
			return it->second.get();
		}

		return nullptr;
	}

#pragma endregion 

#pragma region Set

#pragma endregion 


private:

	// オブジェクトの走査
	void ScanningObjects(nlohmann::json& object, std::map<std::string, std::unique_ptr<LevelData::ObjectData>>& objects);


private:

	// JSONファイルから読み込んだ情報をまとめおく変数
	unique_ptr<LevelData> levelData_;
};

