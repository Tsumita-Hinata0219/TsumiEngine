#pragma once
#include "../Base/BaseResource.h"
#include "../Descriptor/Allocator/DescriptorAllocator.h"
#include "../../Core/DirectXManager/DirectXManager.h"
#include <DirectXTex.h>

using namespace Microsoft::WRL;
using namespace DirectX;


/* DirectX12のテクスチャ */
class TextureResource : public BaseResurce {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TextureResource();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TextureResource();

	/// <summary>
	/// ファイルの読み込み
	/// </summary>
	bool LoadFromFile(const std::wstring& filepath);
	
	/// <summary>
	/// 生成
	/// </summary>
	void CreateRTV();
	void CreateSRV();
	void CreateUAV();

	/// <summary>
	/// GPUHandleの取得
	/// </summary>
	const DescriptorHandle& GetSRVHandle() const { return srvHandle_; }
	const DescriptorHandle& GetRTVHandle() const { return rtvHandle_; }
	const DescriptorHandle& GetUAVHandle() const { return uavHandle_; }

	/// <summary>
	/// リソースの取得
	/// </summary>
	/// <returns></returns>
	ID3D12Resource* GetResource() const { 
		return resource_.Get();
	}

private:
	DescriptorHandle srvHandle_;
	DescriptorHandle rtvHandle_;
	DescriptorHandle uavHandle_;
};



/// <summary>
/// コンストラクタ
/// </summary>
inline TextureResource::TextureResource() {}


/// <summary>
/// デストラクタ
/// </summary>
inline TextureResource::~TextureResource() {}


/// <summary>
/// ファイルの読み込み
/// </summary>
inline bool TextureResource::LoadFromFile(const std::wstring& filepath)
{
	return false;
}


/// <summary>
/// 生成
/// </summary>
inline void TextureResource::CreateRTV() 
{

}
inline void TextureResource::CreateSRV()
{

}
inline void TextureResource::CreateUAV()
{
	auto device = DirectXManager::GetInstance()->GetDevice();
	uavHandle_ = DescriptorAllocator::AllocateUAV();

	D3D12_UNORDERED_ACCESS_VIEW_DESC desc = {};
	desc.Format = resources_[0]->GetDesc().Format;
	desc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2D;

	device->CreateUnorderedAccessView(resources_[0].Get(), nullptr, &desc, uavHandle_.cpuHandle);
}
