#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>
#include <dxgidebug.h>
#include <dxcapi.h>
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxcompiler.lib")

#include <assert.h>

#include "../Base/DXCommon/DirectXCommon.h"
#include "../CommandManager/CommandManager.h"
#include "DescriptorManager/DescriptorManager.h"
#include "Math/MyMath.h"
#include "Math/Struct.h"


/* BufferResourceクラス */
template<typename T>
class BufferResource {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	BufferResource() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BufferResource() = default;

	/// <summary>
	/// Resource作成
	/// </summary>
	void CreateResource(UINT itemCount = 1);
	void CreateCBV(UINT itemCount = 1);

	/// <summary>
	/// VertexBufferViewの作成
	/// </summary>
	void CreateVertexBufferView();

	/// <summary>
	/// IndexBufferViewの作成
	/// </summary>
	void CreateIndexBufferView();

	/// <summary>
	/// InstancingResourceの作成
	/// </summary>
	void CreateInstancingResource(uint32_t instancingNum);

	/// <summary>
	/// UAVの作成
	/// </summary>
	void CreateUAV(UINT itemCount = 1);

	/// <summary>
	/// ResourceをマップしてCPUアクセスを可能にする
	/// </summary>
	void Map();

	/// <summary>
	/// Resourceのマップを解除してGPUアクセスを解除する
	/// </summary>
	void UnMap();

	/// <summary>
	/// データを書き込む
	/// </summary>
	void WriteData(const T* data);
	void WriteData(const std::vector<T>& datas, uint32_t num);

	/// <summary>
	/// コマンドを積む
	/// </summary>
	void CommandCall(UINT number);
	void CommandCallSRV(UINT number, uint32_t index);
	void CommandCallInstancingSRV(UINT number);
	void IASetVertexBuffers(UINT number);
	void IASetIndexBuffer();

#pragma region Accessor アクセッサ

	// VertexBufferView
	D3D12_VERTEX_BUFFER_VIEW GetVBV() { return this->vertexBufferView_; }

	// IndexBufferView
	D3D12_INDEX_BUFFER_VIEW GetIBV() { return this->indexBufferView_; }

#pragma endregion 


private:

	/// <summary>
	/// CBVの生成
	/// </summary>
	void CreateCBVResource();

	/// <summary>
	/// UAVの作成
	/// </summary>
	void CreateUAVResource();


private: 

	// Resource
	Microsoft::WRL::ComPtr<ID3D12Resource> buffer_;

	// VertexBufferView
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_{};
	// IndexBufferView
	D3D12_INDEX_BUFFER_VIEW indexBufferView_{};

	// 作成するResourceの数
	UINT itemCount_ = 1;

	// mappedData
	T* mappedData_{};

	// Index
	uint32_t srvIndex_ = 0;
	uint32_t uavIndex_ = 0;
};


// Resourceの作成
template<typename T>
inline void BufferResource<T>::CreateResource(UINT itemCount) 
{
	// 作成するResourceの要素数
	this->itemCount_ = itemCount;

	// BufferResourceの作成
	CreateCBVResource();
}

// CBVの作成
template<typename T>
inline void BufferResource<T>::CreateCBV(UINT itemCount)
{
	// 作成するResourceの要素数
	this->itemCount_ = itemCount;

	// CBVの作成
	CreateCBVResource();
}

// VertexBufferViewの作成
template<typename T>
inline void BufferResource<T>::CreateVertexBufferView()
{
	vertexBufferView_.BufferLocation = buffer_->GetGPUVirtualAddress();
	vertexBufferView_.SizeInBytes = UINT(sizeof(T) * itemCount_);
	vertexBufferView_.StrideInBytes = UINT(sizeof(T));
}

// IndexBufferViewの作成
template<typename T>
inline void BufferResource<T>::CreateIndexBufferView()
{
	indexBufferView_.BufferLocation = buffer_->GetGPUVirtualAddress();
	indexBufferView_.SizeInBytes = UINT(sizeof(T) * itemCount_);
	indexBufferView_.Format = DXGI_FORMAT_R32_UINT;
}

// InstancingResourceの作成
template<typename T>
inline void BufferResource<T>::CreateInstancingResource(uint32_t instancingNum)
{
	DescriptorManager* descriptor = DescriptorManager::GetInstance();
	srvIndex_ = descriptor->CreateInstancingSRV(instancingNum, this->buffer_, UINT(sizeof(T)));
}

// UAVの作成
template<typename T>
inline void BufferResource<T>::CreateUAV(UINT itemCount)
{
	// 作成するResourceの要素数
	this->itemCount_ = itemCount;

	// UAVの作成
	CreateUAVResource();
}

// ResourceをマップしてCPUアクセスを可能にする
template<typename T>
inline void BufferResource<T>::Map()
{
	// buffer_ が nullptr の場合はエラー
	if (!buffer_) {
		// ログを出力し、アサーションでプログラムを停止させる
		Log("constBuff_ is nullptr. Make sure to create constBuffer before calling Map.");
		assert(false);
		return;
	}

	HRESULT result;
	result = buffer_->Map(0, nullptr, reinterpret_cast<void**>(&mappedData_));
	assert(SUCCEEDED(result));
}

// Resourceのマップを解除してGPUアクセスを解除する
template<typename T>
inline void BufferResource<T>::UnMap()
{
	// buffer_ と mappedData_ が有効な時にUnMap
	if (buffer_ && mappedData_) {
		buffer_->Unmap(0, nullptr);
		mappedData_ = nullptr;
	}
}

// データを書き込む
template<typename T>
inline void BufferResource<T>::WriteData(const T* data)
{
	assert(data != nullptr); // ポインタが有効か確認
	assert(mappedData_ != nullptr); // mappedData_ が初期化されているか確認
	std::memcpy(mappedData_, data, sizeof(T) * itemCount_);
}

template<typename T>
inline void BufferResource<T>::WriteData(const std::vector<T>& datas, uint32_t num)
{
	// ベクトルが空でないことを確認
	assert(!datas.empty());
	// データ数が一致しているか確認する
	assert(num == itemCount_);
	// 実際のデータを書き込む処理
	std::memcpy(mappedData_, datas.data(), sizeof(T) * num);
}

// コマンドを積む
template<typename T>
inline void BufferResource<T>::CommandCall(UINT number)
{
	Commands commands = CommandManager::GetInstance()->GetCommands();
	commands.List->SetGraphicsRootConstantBufferView(number, buffer_->GetGPUVirtualAddress());
}

template<typename T>
inline void BufferResource<T>::CommandCallSRV(UINT number, uint32_t index)
{
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	Commands commands = CommandManager::GetInstance()->GetCommands();
	DescriptorManager* descriptor = DescriptorManager::GetInstance();
	ID3D12DescriptorHeap* desc[] = { dxCommon->GetSrvDescriptorHeap() };
	commands.List->SetDescriptorHeaps(1, desc);
	commands.List->SetGraphicsRootDescriptorTable(number, descriptor->GetSRVHandle(index)._GPU);
}

template<typename T>
inline void BufferResource<T>::CommandCallInstancingSRV(UINT number)
{
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	Commands commands = CommandManager::GetInstance()->GetCommands();
	DescriptorManager* descriptor = DescriptorManager::GetInstance();
	ID3D12DescriptorHeap* desc[] = { dxCommon->GetSrvDescriptorHeap() };
	commands.List->SetDescriptorHeaps(1, desc);
	commands.List->SetGraphicsRootDescriptorTable(number, descriptor->GetSRVHandle(srvIndex_)._GPU);
}

template<typename T>
inline void BufferResource<T>::IASetVertexBuffers(UINT number)
{
	Commands commands = CommandManager::GetInstance()->GetCommands();
	commands.List->IASetVertexBuffers(0, number, &vertexBufferView_);
}

template<typename T>
inline void BufferResource<T>::IASetIndexBuffer()
{
	Commands commands = CommandManager::GetInstance()->GetCommands();
	commands.List->IASetIndexBuffer(&indexBufferView_);
}

// BufferResourceの生成
template<typename T>
inline void BufferResource<T>::CreateCBVResource()
{
	// Resource用のHeap設定
	D3D12_HEAP_PROPERTIES uploadHeapProperties_{};
	uploadHeapProperties_.Type = D3D12_HEAP_TYPE_UPLOAD; // UploadHeapを使う

	// BufferResource。Textureの場合はまた別の設定をする
	D3D12_RESOURCE_DESC vertexResourceDesc_{};
	vertexResourceDesc_.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;

	// Resourceのサイズ
	vertexResourceDesc_.Width = sizeof(T) * itemCount_;

	// Bufferの場合はこれらは1にする決まり
	vertexResourceDesc_.Height = 1;
	vertexResourceDesc_.DepthOrArraySize = 1;
	vertexResourceDesc_.MipLevels = 1;
	vertexResourceDesc_.SampleDesc.Count = 1;

	// Bufferの場合はこれにする決まり
	vertexResourceDesc_.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// 実際にBufferResourceを作る
	HRESULT hr_;
	hr_ = DirectXCommon::GetInstance()->GetDevice()->CreateCommittedResource(
		&uploadHeapProperties_, D3D12_HEAP_FLAG_NONE,
		&vertexResourceDesc_, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&buffer_));
	assert(SUCCEEDED(hr_));
	if (FAILED(hr_)) {
		// エラーハンドリング
		std::cerr << "CreateCommittedResource failed: " << std::hex << hr_ << std::endl;
	}
}

// UAVの作成
template<typename T>
inline void BufferResource<T>::CreateUAVResource()
{
	// Resource用のHeap設定
	D3D12_HEAP_PROPERTIES uploadHeapProperties_{};
	//uploadHeapProperties_.Type = D3D12_HEAP_TYPE_UPLOAD; // UploadHeapを使う
	uploadHeapProperties_.Type = D3D12_HEAP_TYPE_DEFAULT; // DefaultHeapを使う

	// BufferResource。Textureの場合はまた別の設定をする
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	// 専用のフラグを立てる
	resourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
	// Resourceのサイズ
	resourceDesc.Width = sizeof(T) * itemCount_;
	// Bufferの場合はこれらは1にする決まり
	resourceDesc.Height = 1;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.MipLevels = 1;
	resourceDesc.SampleDesc.Count = 1;
	// Bufferの場合はこれにする決まり
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// 実際にBufferResourceを作る
	HRESULT hr_;
	hr_ = DirectXCommon::GetInstance()->GetDevice()->CreateCommittedResource(
		&uploadHeapProperties_, D3D12_HEAP_FLAG_NONE,
		&resourceDesc, D3D12_RESOURCE_STATE_COMMON, nullptr,
		IID_PPV_ARGS(&buffer_));

	// DescriptorManagerでUAVを作る
	DescriptorManager* descriptor = DescriptorManager::GetInstance();
	this->uavIndex_ = descriptor->CreateUAV(this->buffer_, sizeof(T), itemCount_);

	assert(SUCCEEDED(hr_));
	if (FAILED(hr_)) {
		// エラーハンドリング
		std::cerr << "CreateCommittedResource failed: " << std::hex << hr_ << std::endl;
	}
}
