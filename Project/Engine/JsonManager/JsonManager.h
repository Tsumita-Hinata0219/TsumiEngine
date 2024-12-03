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

	/// <summary>
	/// マップを空にする
	/// </summary>
	void Clear() { entityMap_.clear(); }


#pragma region Accessor アクセッサ

	/// <summary>
	/// EntityDataのリストの取得
	/// </summary>
	const std::vector<std::unique_ptr<EntityData>>* GetEntityData(const std::string& key) const {
		auto it = entityMap_.find(key);
		if (it != entityMap_.end()) {
			return &it->second;
		}
		return nullptr; // キーが存在しない場合
	}

	/// <summary>
	/// データを追加
	/// </summary>
	void AddEntityData(std::unique_ptr<EntityData> entity) {
		entityMap_[entity->entityName].emplace_back(std::move(entity));
	}

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

