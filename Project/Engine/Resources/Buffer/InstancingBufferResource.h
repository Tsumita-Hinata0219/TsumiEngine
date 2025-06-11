#pragma once
#include "../Base/BaseResource.h"


/* インスタンス描画バッファ */
template<typename T>
class InstancingBufferResource : public BaseResource {

public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    InstancingBufferResource();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~InstancingBufferResource();

    /// <summary>
    /// 生成
    /// </summary>
    void Create(UINT elementCount, const T* initialData = nullptr);
    
    /// <summary>
    /// バインド
    /// </summary>
    void Bind(UINT slot = 1) const;

    /// <summary>
    /// Viewの取得
    /// </summary>
    const D3D12_VERTEX_BUFFER_VIEW& GetView() const { return vbv_; }

private:
    D3D12_VERTEX_BUFFER_VIEW vbv_{};
    UINT elementCount_ = 0;
};



/// <summary>
/// コンストラクタ
/// </summary>
template<typename T>
inline InstancingBufferResource<T>::InstancingBufferResource() {}


/// <summary>
/// デストラクタ
/// </summary>
template<typename T>
inline InstancingBufferResource<T>::~InstancingBufferResource() {}


/// <summary>
/// 生成
/// </summary>
template<typename T>
inline void InstancingBufferResource<T>::Create(UINT elementCount, const T* initialData)
{
    elementCount_ = elementCount;
    UINT bufferSize = sizeof(T) * elementCount;

    auto device = DirectXManager::GetInstance()->GetDevice();

    CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);
    CD3DX12_RESOURCE_DESC bufferDesc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

    Microsoft::WRL::ComPtr<ID3D12Resource> resource;
    HRESULT hr = device->CreateCommittedResource(
        &heapProps,
        D3D12_HEAP_FLAG_NONE,
        &bufferDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&resource)
    );
    assert(SUCCEEDED(hr));
    resources_.push_back(resource);

    if (initialData) {
        void* mapped = nullptr;
        resource->Map(0, nullptr, &mapped);
        memcpy(mapped, initialData, bufferSize);
        resource->Unmap(0, nullptr);
    }

    vbv_.BufferLocation = resource->GetGPUVirtualAddress();
    vbv_.SizeInBytes = bufferSize;
    vbv_.StrideInBytes = sizeof(T);
}


/// <summary>
/// バインド
/// </summary>
template<typename T>
inline void InstancingBufferResource<T>::Bind(UINT slot) const
{
    auto cmd = CommandManager::GetInstance()->GetCommands();
    cmd.List->IASetVertexBuffers(slot, 1, &vbv_);
}