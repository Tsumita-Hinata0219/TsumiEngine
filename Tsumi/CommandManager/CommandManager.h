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

class DirectXCommon;


/* CommandManagerクラス */
class CommandManager {

private: // シングルトンデザインパターン

	// コンストラクタ、デストラクタ
	CommandManager() = default;
	~CommandManager() = default;
	CommandManager(const CommandManager&) = delete;
	const CommandManager& operator=(const CommandManager&) = delete;


public: // メンバ関数

	// インスタンスの取得
	static CommandManager* GetInstance() {
		static CommandManager instance;
		return &instance;
	}

	// 初期化処理
	void Initialize();

	// 解放処理
	void Finalize();


#pragma region Accessor アクセスメソッド

	// コマンドキュー
	ID3D12CommandQueue* const GetQueue() { return this->queue_.Get(); }
	void SetQueue(ID3D12CommandQueue* const setQueue) { this->queue_ = setQueue; }

	// アロケータ
	ID3D12CommandAllocator* const GetAllocator() { return this->allocator_.Get(); }
	void SetAllocator(ID3D12CommandAllocator* const setAllocator) { this->allocator_ = setAllocator; }

	// リスト
	ID3D12GraphicsCommandList* const GetList() { return this->list_.Get(); }
	void SetList(ID3D12GraphicsCommandList* const setList) { this->list_ = setList; }

#pragma endregion 


private: // メンバ関数

	// コマンドキューを生成する
	void CreateCommandQueue();

	// コマンドアロケータを生成する
	void CreateCommandAllocator();

	// コマンドリストを生成する
	void CreateCommandList();


private: // メンバ変数

	// DirectXCommon
	DirectXCommon* dxCommon_ = nullptr;

	// コマンドキュー
	ComPtr<ID3D12CommandQueue> queue_;

	// コマンドアロケータ
	ComPtr<ID3D12CommandAllocator> allocator_;

	// コマンドリスト
	ComPtr<ID3D12GraphicsCommandList> list_;
};

