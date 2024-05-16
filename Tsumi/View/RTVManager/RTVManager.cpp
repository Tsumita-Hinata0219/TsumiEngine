#include "RTVManager.h"



// 初期化処理
void RTVManager::Initialize()
{
}


// 開始処理
void RTVManager::BeginFrame()
{
	// 使用サイズが超過していないかチェック
	// 超えていたらassert
	assert(index_ >= RTV_Index_Max, Log("RTVの使用サイズ超過"));
}


// 終了処理
void RTVManager::EndFrame() {}


// ImGui描画
void RTVManager::DrawImGui()
{
	ImGui::Text("RTV_Index : %d", index_);
}


// RTVDataの検索
RTVData* RTVManager::CheckRTV(std::string name)
{
	// 検索
	const auto& rtv = rtvMap_.find(name);

	// ヒットしたらそのポインタを返す
	if (rtv != rtvMap_.end()) {
		return &rtv->second;
	}

	// なければNULLを返す
	return nullptr;
}


// 指定RTVDataの破棄
void RTVManager::RemoveRTVData(std::string name)
{
	// 検索
	const auto& rtv = rtvMap_.find(name);

	// なかったらreturn
	if (rtv == rtvMap_.end()) { return; }

	// ヒットしたら破棄
	rtvMap_.erase(name);
}


// 全RTVDataの破棄
void RTVManager::AllRemoveRTVData()
{
	rtvMap_.clear();
}
