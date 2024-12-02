#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cmath>
#include <numbers>


#include "json.hpp"

#include "3D/Model/ModelManager/ModelManager.h"

#include "Math/MyMath.h"
#include "GameObject/GameObject.h"



struct ColliderData {
	std::string type;
	Vector3 center;
	Vector3 size;
};
struct LevelData {

	struct ObjectData {
		std::string type;
		std::string file_name;
		SRTN srt;
		std::map<std::string, std::unique_ptr<ObjectData>> children;
	};
	std::map<std::string, std::unique_ptr<ObjectData>> objects;
};
struct EntityData {
	std::string type;
	std::string entityName;
	SRTN srt;
	std::map<std::string, std::unique_ptr<EntityData>> children;
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

	/// <summary>
	/// インスタンスの取得
	/// </summary>
	static JsonManager* GetInstance();

	/// <summary>
	/// シーンのJsonの読み込み
	/// </summary>
	void LoadSceneFile(const std::string& path, const std::string& fileName);


#pragma region Accessor アクセッサ



#pragma endregion 


private:

	/// <summary>
	/// オブジェクトの走査
	/// </summary>
	std::unique_ptr<EntityData> ScanningEntityData(const std::string& path, nlohmann::json& object);

	/// <summary>
	/// タイプ
	/// </summary>
	std::string ScanningType(nlohmann::json& object);

	/// <summary>
	/// エンティティ名
	/// </summary>
	std::string ScanningEntityName(nlohmann::json& object);

	/// <summary>
	/// SRTの読み込み
	/// </summary>
	SRTN ScanningSRT(nlohmann::json& object);


private: // メンバ変数

	// 読み込んだ情報をまとめておくコンテナ
	std::map<const std::string, std::vector<std::unique_ptr<EntityData>>> entityMap_;

};

