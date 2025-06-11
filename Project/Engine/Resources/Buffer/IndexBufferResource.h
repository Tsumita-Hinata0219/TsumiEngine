#pragma once
#include"../Base/BaseResource.h"
#include "../../Graphics/CommandManager/CommandManager.h"


/* インデックスバッファ(IBV) */
template<typename IndexType = uint32_t>
class IndexBufferResource : public BaseResource {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	IndexBufferResource();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~IndexBufferResource();

	/// <summary>
	/// 生成
	/// </summary>
	void Create(const std::vector<IndexType>& indices);

	/// <summary>
	/// バインド
	/// </summary>
	void Bind() const;

	/// <summary>
	/// indicesのサイズ取得
	/// </summary>
	/// <returns></returns>
	UINT GetIndexCount() const { return static_cast<UINT>(indices_.size()); }

	/// <summary>
	/// Viewの取得
	/// </summary>
	D3D12_INDEX_BUFFER_VIEW GetView() const { return ibView_; }

private:
	std::vector<IndexType> indices_;
	D3D12_INDEX_BUFFER_VIEW ibView_{};
};



/// <summary>
/// コンストラクタ
/// </summary>
template<typename IndexType>
inline IndexBufferResource<IndexType>::IndexBufferResource()
{
}


/// <summary>
/// デストラクタ
/// </summary>
template<typename IndexType>
inline IndexBufferResource<IndexType>::~IndexBufferResource()
{
}



/// <summary>
/// 生成
/// </summary>
template<typename IndexType>
inline void IndexBufferResource<IndexType>::Create(const std::vector<IndexType>& indices)
{
	indices_ = indices;
	UINT bufferSize = sizeof(IndexType) * static_cast<UINT>(indices.size());

	auto device = DirectXManager::GetInstance()->GetDevice();
	CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC resDesc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	ComPtr<ID3D12Resource> ib;
	HRESULT hr = device->CreateCommittedResource(
		&heapProps,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&ib)
	);
	assert(SUCCEEDED(hr));
	resources_.push_back(ib);

	void* mapped = nullptr;
	ib->Map(0, nullptr, &mapped);
	std::memcpy(mapped, indices.data(), bufferSize);
	ib->Unmap(0, nullptr);

	ibView_.BufferLocation = ib->GetGPUVirtualAddress();
	ibView_.SizeInBytes = bufferSize;
	ibView_.Format = std::is_same_v<IndexType, uint16_t> ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT;
}


/// <summary>
/// バインド
/// </summary>
template<typename IndexType>
inline void IndexBufferResource<IndexType>::Bind() const
{
	auto cmd = CommandManager::GetInstance()->GetCommands();
	cmd.List->IASetIndexBuffer(&ibView_);
}
