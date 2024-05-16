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


// RTVProperty
struct RTVProperty {
	ComPtr<ID3D12DescriptorHeap> DescriptorHeap;
	D3D12_RENDER_TARGET_VIEW_DESC Desc{};
	D3D12_CPU_DESCRIPTOR_HANDLE Handles;
	D3D12_CPU_DESCRIPTOR_HANDLE StartHandle;
	ComPtr<ID3D12Resource> Resources;
	Vector4 color;
};


/* RTVDataクラス */
class RTVData {

public: // メンバ関数

	// コンストラクタ、デストラクタ
	RTVData(uint32_t index, RTVProperty rtv);
	~RTVData();

#pragma region Get

	// RTVの取得
	RTVProperty GetRTVPrope() { return this->rtvPrope_; }

#pragma endregion 

private: // メンバ変数

	// インデックス
	uint32_t index_ = 0;

	// RTV
	RTVProperty rtvPrope_{};
};

