#include "DescriptorManager.h"



// インスタンスの取得
DescriptorManager* DescriptorManager::GetInstance() 
{
	static DescriptorManager instance;
	return &instance;
}


// 初期化処理
void DescriptorManager::Init() 
{
	// DirectXCommonのインスタンス取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	descriptorSize_.SRV =
		dxCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	descriptorSize_.RTV =
		dxCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	descriptorSize_.DSV =
		dxCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	index_ = 0;
}


// Descriptorがindex数を超えていないか
void DescriptorManager::BeginFrame() 
{
	if (index_ >= descriptor_Max) {

		Log("The number of DescripterIndexes has exceeded the limit.");
		assert(0);
	}
}


// indexをクリアにする
void DescriptorManager::Clear() 
{
	index_ = 0;
}


// SRVを作成する
uint32_t DescriptorManager::CreateInstancingSRV(uint32_t instancingNum, ComPtr<ID3D12Resource>& resource, UINT size) 
{
	// indexをインクリメント
	index_++;

	// SRVの設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
	srvDesc.Buffer.FirstElement = 0;
	srvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
	srvDesc.Buffer.NumElements = instancingNum;
	srvDesc.Buffer.StructureByteStride = size;

	// SRVを作成するDescriptorHeapの場所を決める
	AssignSRVHandles();
	// CPUとGPUの.ptrをずらす
	ShiftSRVHandlePtr();
	// SRVの生成
	CreateShaderResourceView(resource, srvDesc, index_);

	return index_;
}
uint32_t DescriptorManager::CreateRenderTextureSRV(ComPtr<ID3D12Resource>& resource) 
{
	// indexをインクリメント
	index_++;

	// SRVの設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	// SRVを作成するDescriptorHeapの場所を決める
	AssignSRVHandles();
	// CPUとGPUの.ptrをずらす
	ShiftSRVHandlePtr();
	// SRVの生成
	CreateShaderResourceView(resource, srvDesc, index_);

	return index_;
}
uint32_t DescriptorManager::CreateRenderTextureDepthSRV(ComPtr<ID3D12Resource>& resource)
{
	// indexをインクリメント
	index_++;

	// SRVの設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	// SRVを作成するDescriptorHeapの場所を決める
	AssignSRVHandles();
	// CPUとGPUの.ptrをずらす
	ShiftSRVHandlePtr();
	// SRVの生成
	CreateShaderResourceView(resource, srvDesc, index_);

	return index_;
}


/// <summary>
/// SRVを作成するDescriptorHeapの場所を決める
/// </summary>
void DescriptorManager::AssignSRVHandles()
{
	// DirectXCommonのインスタンス取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	srvHandle_[index_]._CPU = GetCPUDescriptorHandle(
		dxCommon->GetSrvDescriptorHeap(),
		descriptorSize_.SRV,
		index_);

	srvHandle_[index_]._GPU = GetGPUDescriptorHandle(
		dxCommon->GetSrvDescriptorHeap(),
		descriptorSize_.SRV,
		index_);
}


// CPUとGPUの.ptrをずらす
void DescriptorManager::ShiftSRVHandlePtr() 
{
	// DirectXCommonのインスタンス取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	srvHandle_[index_]._CPU.ptr +=
		dxCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	
	srvHandle_[index_]._GPU.ptr +=
		dxCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}


// indexをインクリメント
void DescriptorManager::IncrementIndex() 
{
	index_++;
}


// DescriptorTableを設定する
void DescriptorManager::SetGraphicsRootDescriptorTable(UINT rootPatramerterIndex, uint32_t texHandle) 
{
	// Commandの取得
	Commands commands = CommandManager::GetInstance()->GetCommands();

	commands.List->SetGraphicsRootDescriptorTable(
		rootPatramerterIndex, 
		srvHandle_[texHandle]._GPU);
}


// SRVの生成
void DescriptorManager::CreateShaderResourceView(ComPtr<ID3D12Resource> resource, D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc, uint32_t index) 
{
	// DirectXCommonのインスタンス取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	dxCommon->GetDevice()->CreateShaderResourceView(
		resource.Get(),
		&srvDesc,
		srvHandle_[index]._CPU);
}


// DescriptorHandleを取得する
D3D12_CPU_DESCRIPTOR_HANDLE DescriptorManager::GetCPUDescriptorHandle(ComPtr<ID3D12DescriptorHeap> descriptorHeap, uint32_t descriptorSize, uint32_t index)
{
	D3D12_CPU_DESCRIPTOR_HANDLE handleCPU = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
	handleCPU.ptr += (static_cast<unsigned long long>(descriptorSize) * index);
	return handleCPU;
}
D3D12_GPU_DESCRIPTOR_HANDLE DescriptorManager::GetGPUDescriptorHandle(ComPtr<ID3D12DescriptorHeap> descriptorHeap, uint32_t descriptorSize, uint32_t index)
{
	D3D12_GPU_DESCRIPTOR_HANDLE handleGPU = descriptorHeap->GetGPUDescriptorHandleForHeapStart();
	handleGPU.ptr += (static_cast<unsigned long long>(descriptorSize) * index);
	return handleGPU;
}

