#include "ResourceBase.h"


/// <summary>
/// リソースを設定
/// </summary>
void ResourceBase::SetResource(Microsoft::WRL::ComPtr<ID3D12Resource> resource)
{
	assert(resource != nullptr);
	resource_ = resource;
}


/// <summary>
/// 名前を付ける
/// </summary>
void ResourceBase::SetName(const std::wstring& name)
{
	name_ = name;
	if (resource_) {
		resource_->SetName(name.c_str());
	}
}


/// <summary>
/// GPU仮想アドレスを取得
/// </summary>
D3D12_GPU_VIRTUAL_ADDRESS ResourceBase::GetGPUVirtualAddress() const
{
	assert(resource_);
	return resource_->GetGPUVirtualAddress();
}


/// <summary>
/// サイズを設定
/// </summary>
void ResourceBase::SetSize(UINT size)
{
	size_ = size;
}


/// <summary>
/// サイズを取得
/// </summary>
UINT ResourceBase::GetSize() const {
	return size_;
}