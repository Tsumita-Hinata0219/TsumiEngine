#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>
#include <dxgidebug.h>
#include <dxcapi.h>
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxcompiler.lib")

#include "MyMath.h"
#include "Struct.h"

#include"DescriptorManager.h"

#define RTV_Index_Max 16


// RTVData
struct RTVData {
	ComPtr<ID3D12DescriptorHeap> DescriptorHeap;
	D3D12_RENDER_TARGET_VIEW_DESC Desc{};
	D3D12_CPU_DESCRIPTOR_HANDLE Handles;
	D3D12_CPU_DESCRIPTOR_HANDLE StartHandle;
	ComPtr<ID3D12Resource> Resources;
	Vector4 color;
};

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

