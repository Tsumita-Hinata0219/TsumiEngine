#pragma once

#include "RTVData.h"

#define RTV_Index_Max 16


/* RTVManagerクラス */
class RTVManager {

private: // シングルトンデザインパターン

	// コンストラクタ、デストラクタ
	RTVManager() = default;
	~RTVManager() = default;
	RTVManager(const RTVManager&) = delete;
	const RTVManager& operator=(const RTVManager&) = delete;


public: // メンバ関数

	// 初期化処理
	void Initialize();

	// 開始処理、終了処理
	void BeginFrame();
	void EndFrame();

	// ImGui描画
	void DrawImGui();

private:

	// RTVDataの検索
	RTVData* CheckRTV(std::string name);

	// 指定RTVDataの破棄
	void RemoveRTVData(std::string name);

	// 全RTVDataの破棄
	void AllRemoveRTVData();


private: // メンバ変数

	// 使用サイズ
	uint32_t index_;

	// RTVデータ
	std::map<std::string, RTVData> rtvMap_;
};

