#include "ResourceBase.h"


/// <summary>
/// リソースを設定
/// </summary>
void BaseResurce::SetResource(Microsoft::WRL::ComPtr<ID3D12Resource> resource)
{
	assert(resource != nullptr);
	resource_ = resource;
}


/// <summary>
/// 名前を付ける
/// </summary>
void BaseResurce::SetName(const std::wstring& name)
{
	name_ = name;
	if (resource_) {
		resource_->SetName(name.c_str());
	}
}


/// <summary>
/// GPU仮想アドレスを取得
/// </summary>
D3D12_GPU_VIRTUAL_ADDRESS BaseResurce::GetGPUVirtualAddress() const
{
	assert(resource_);
	return resource_->GetGPUVirtualAddress();
}


/// <summary>
/// サイズを設定
/// </summary>
void BaseResurce::SetSize(UINT size)
{
	size_ = size;
}


/// <summary>
/// サイズを取得
/// </summary>
UINT BaseResurce::GetSize() const {
	return size_;
}