#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <vector>
#include"../Base/ResourceBase.h"
#include "../../Graphics/CommandManager/CommandManager.h"


/* 頂点バッファクラス */
template <typename VertexType>
class VertexBufferResource : public BaseResurce {

public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    VertexBufferResource();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~VertexBufferResource();

    /// <summary>
    /// 生成
    /// </summary>
    void Create(const std::vector<VertexType>& vertices);

    /// <summary>
    /// バインド
    /// </summary>
    void Bind(UINT slot = 0) const;

    /// <summary>
    /// verticesのサイズ取得
    /// </summary>
    UINT GetVertexCount() const { return static_cast<UINT>(vertices_.size()); }
    
    /// <summary>
    /// Viewの取得
    /// </summary>
    D3D12_VERTEX_BUFFER_VIEW GetView() const { return vbView_; }

private:

    std::vector<VertexType> vertices_;
    D3D12_VERTEX_BUFFER_VIEW vbView_;
};



/// <summary>
/// コンストラクタ
/// </summary>
template<typename VertexType>
inline VertexBufferResource<VertexType>::VertexBufferResource()
{
}


/// <summary>
/// デストラクタ
/// </summary>
template<typename VertexType>
inline VertexBufferResource<VertexType>::~VertexBufferResource()
{
}


/// <summary>
/// 生成
/// </summary>
template<typename VertexType>
inline void VertexBufferResource<VertexType>::Create(const std::vector<VertexType>& vertices)
{
    vertices_ = vertices;
    UINT bufferSize = sizeof(VertexType) * static_cast<UINT>(vertices.size());

    auto device = DirectXManager::GetInstance()->GetDevice();
    CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);
    CD3DX12_RESOURCE_DESC resDesc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

    ComPtr<ID3D12Resource> vb;
    HRESULT hr = device->CreateCommittedResource(
        &heapProps,
        D3D12_HEAP_FLAG_NONE,
        &resDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&vb)
    );
    assert(SUCCEEDED(hr));
    resources_.push_back(vb);

    // マップしてコピー
    void* mapped = nullptr;
    vb->Map(0, nullptr, &mapped);
    std::memcpy(mapped, vertices.data(), bufferSize);
    vb->Unmap(0, nullptr);

    // ビュー作成
    vbView_.BufferLocation = vb->GetGPUVirtualAddress();
    vbView_.StrideInBytes = sizeof(VertexType);
    vbView_.SizeInBytes = bufferSize;
}


/// <summary>
/// バインド
/// </summary>
template<typename VertexType>
inline void VertexBufferResource<VertexType>::Bind(UINT slot) const
{
    auto cmd = CommandManager::GetInstance()->GetCommands();
    cmd.List->IASetVertexBuffers(slot, 1, &vbView_);
}
