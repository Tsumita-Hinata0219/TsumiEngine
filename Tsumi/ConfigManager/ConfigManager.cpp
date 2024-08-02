#include "ConfigManager.h"



// グループ作成
void ConfigManager::CreateGroup(const std::string& groupName)
{
	// 指定された名前で検索をかける
	auto it = datas_.find(groupName);

	// ヒットしたらreturn
	if (it != datas_.end()) {
		return;
	}

	// 見つからなければ追加
	datas_[groupName];
}


// 項目のセット
void ConfigManager::SetValue(const std::string& groupName, const std::string& key, int32_t value)
{
	// グループの参照を取得
	ConfigGroup& group = datas_[groupName];

	// 指定された名前で検索をかける
	auto it = group.items.find(key);

	// ヒットしなかったら項目を作る
	if (it == group.items.end()) {
		group.items[key];
	}

	// 項目のデータを設定
	group.items[key].value = value;
}
void ConfigManager::SetValue(const std::string& groupName, const std::string& key, float value)
{
	// グループの参照を取得
	ConfigGroup& group = datas_[groupName];

	// 指定された名前で検索をかける
	auto it = group.items.find(key);

	// ヒットしなかったら項目を作る
	if (it == group.items.end()) {
		group.items[key];
	}

	// 項目のデータを設定
	group.items[key].value = value;
}
void ConfigManager::SetValue(const std::string& groupName, const std::string& key, const Vector3& value)
{
	// グループの参照を取得
	ConfigGroup& group = datas_[groupName];

	// 指定された名前で検索をかける
	auto it = group.items.find(key);

	// ヒットしなかったら項目を作る
	if (it == group.items.end()) {
		group.items[key];
	}

	// 項目のデータを設定
	group.items[key].value = value;
}
