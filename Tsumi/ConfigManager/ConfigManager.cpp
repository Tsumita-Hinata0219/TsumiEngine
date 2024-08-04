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
	ConfigGroup& group = GetGroup(groupName);

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


// 更新処理
void ConfigManager::DrawImGui()
{
	if (!ImGui::Begin("Config Manager", nullptr, ImGuiWindowFlags_MenuBar)) {
		ImGui::End();
		return;
	}
	if (!ImGui::BeginMenuBar()) return;

	
	// 各グループについて
	for (std::map<std::string, ConfigGroup>::iterator itGroup = datas_.begin(); itGroup != datas_.end(); ++itGroup) {

		// グループ名とグループを取得
		const std::string& groupName = itGroup->first;
		ConfigGroup& group = itGroup->second;

		// グループのメニューを追加する処理
		if (!ImGui::BeginMenu(groupName.c_str()))
			continue;

		// 各項目について
		for (std::map<std::string, ConfigItem>::iterator itItem = group.items.begin(); itItem != group.items.end(); ++itItem) {

			// 項目名と項目を取得
			const std::string& itemName = itItem->first;
			ConfigItem& item = itItem->second;

			// int32_t型の値を保持していれば
			if (std::holds_alternative<int32_t>(item.value)) {
				int32_t* ptr = std::get_if<int32_t>(&item.value);
				ImGui::DragInt(itemName.c_str(), ptr, 1);
			}
			// flaot型の値を保持していれば
			else if (std::holds_alternative<float>(item.value)) {
				float* ptr = std::get_if<float>(&item.value);
				ImGui::DragFloat(itemName.c_str(), ptr, 0.01f);
			}
			// Vector3型の値を保持していれば
			else if (std::holds_alternative<Vector3>(item.value)) {
				Vector3* ptr = std::get_if<Vector3>(&item.value);
				ImGui::DragFloat3(itemName.c_str(), &ptr->x, 0.1f);
			}
		}

		ImGui::EndMenu();
	}


	ImGui::EndMenuBar();
	ImGui::End();
}
