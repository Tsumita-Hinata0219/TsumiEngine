#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>
#include <dxgidebug.h>
#include <dxcapi.h>
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxcompiler.lib")

#include <wrl.h>
using Microsoft::WRL::ComPtr;
using namespace std;


/* CommandManagerクラス */
class CommandManager {

private: // シングルトンデザインパターン


public: // メンバ関数

	// 初期化処理
	void Initialize();

	// 解放処理
	void Finalize();


#pragma region Accessor アクセスメソッド

	// コマンドキュー
	ID3D12CommandQueue* const GetQueue() { return this->queue.Get(); }
	void SetQueue(ID3D12CommandQueue* const setQueue) { this->queue = setQueue; }

	// アロケータ
	ID3D12CommandAllocator* const GetAllocator() { return this->allocator.Get(); }
	void SetAllocator(ID3D12CommandAllocator* const setAllocator) { this->allocator = setAllocator; }

	// リスト
	ID3D12GraphicsCommandList* const GetList() { return this->list.Get(); }
	void SetList(ID3D12GraphicsCommandList* const setList) { this->list = setList; }

#pragma endregion 


private: // メンバ関数

	// コマンドキューを生成する
	void CreateCommandQueue();

	// コマンドアロケータを生成する
	void CreateCommandAllocator();

	// コマンドリストを生成する
	void CreateCommandList();


private: // メンバ変数

	// コマンドキュー
	ComPtr<ID3D12CommandQueue> queue;

	// コマンドアロケータ
	ComPtr<ID3D12CommandAllocator> allocator;

	// コマンドリスト
	ComPtr<ID3D12GraphicsCommandList> list;
};

