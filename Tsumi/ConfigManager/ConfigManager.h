#pragma once

#include <variant>
#include <stdexcept>

#include "Math/MyMath.h"



// 項目構造体
struct ConfigItem {
	// 項目の値
	std::variant<int32_t, float, Vector3> value;
};
// グループ構造体
struct ConfigGroup {
	std::map<std::string, ConfigItem> items;
};


/* 調整項目クラス */
class ConfigManager {

private: // シングルトンデザインパターン

	// コンストラクタ、デストラクタ
	ConfigManager() = default;
	~ConfigManager() = default;
	ConfigManager(const ConfigManager&) = delete;
	const ConfigManager& operator=(const ConfigManager&) = delete;


public: // メンバ関数

	// インスタンス取得
	static ConfigManager* GetInstance() {
		static ConfigManager instance;
		return &instance;
	}

	/// <summary>
	/// グループ作成
	/// </summary>
	/// <param name="groupName"> グループ名 </param>
	void CreateGroup(const std::string& groupName);

	/// <summary>
	/// 項目のセット
	/// </summary>
	/// <param name="groupName"> グループ名 </param>
	/// <param name="key"> 項目名 </param>
	void SetValue(const std::string& groupName, const std::string& key, int32_t value);
	void SetValue(const std::string& groupName, const std::string& key, float value);
	void SetValue(const std::string& groupName, const std::string& key, const Vector3& value);

	/// <summary>
	/// 更新処理
	/// </summary>
	void DrawImGui();

#pragma region Accessor アクセッサ

	// グループの取得
	ConfigGroup& GetGroup(const std::string& groupName) {
		// 指定された名前で検索をかける
		auto it = datas_.find(groupName);

		// ヒットしたらそのグループをreturn
		if (it != datas_.end()) {
			return it->second;
		}

		// 見つからなかった場合のエラーハンドリング
		Log("\n指定されたグループは存在しません\n新しくグループを作成するか、指定名を修正してください\n");
		throw std::runtime_error("Group not found: " + groupName);
	}

#pragma endregion 


private: // メンバ変数

	// 全データ
	std::map<std::string, ConfigGroup> datas_;

};

