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
}
void ConfigManager::SetValue(const std::string& groupName, const std::string& key, float value)
{
}
void ConfigManager::SetValue(const std::string& groupName, const std::string& key, const Vector3& value)
{
}
