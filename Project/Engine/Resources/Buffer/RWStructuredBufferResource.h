#pragma once
#include "../Base/BaseResource.h"
#include "../Descriptor/Allocator/DescriptorAllocator.h"

/* 読み取り&書き込みバッファ(UAV) */
template<typename T>
class RWStructuredBufferResource : public BaseResource {

public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    RWStructuredBufferResource();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~RWStructuredBufferResource();

    /// <summary>
    /// 生成
    /// </summary>
    void Create(UINT elementCount, bool createInitialData = false, const T* initialData = nullptr);
    
    /// <summary>
    /// バインド
    /// </summary>
    void BindUAV(UINT rootParamIndex) const;

    /// <summary>
    /// GPUHandleの取得
    /// </summary>
    D3D12_GPU_DESCRIPTOR_HANDLE GetUAVGPUHandle() const { return uavHandle_.gpuHandle; }

private:
    DescriptorHandle uavHandle_;
    UINT elementCount_ = 0;
};



/// <summary>
/// コンストラクタ
/// </summary>
template<typename T>
inline RWStructuredBufferResource<T>::RWStructuredBufferResource() {}


/// <summary>
/// デストラクタ
/// </summary>
template<typename T>
inline RWStructuredBufferResource<T>::~RWStructuredBufferResource() {}


/// <summary>
/// 生成
/// </summary>
template<typename T>
inline void RWStructuredBufferResource<T>::Create(UINT elementCount, bool createInitialData, const T* initialData)
{
    elementCount_ = elementCount;
    UINT bufferSize = sizeof(T) * elementCount;

    auto device = DirectXManager::GetInstance()->GetDevice();

    CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_DEFAULT);
    CD3DX12_RESOURCE_DESC resDesc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);
    resDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
    resDesc.StructureByteStride = sizeof(T);

    Microsoft::WRL::ComPtr<ID3D12Resource> resource;
    HRESULT hr = device->CreateCommittedResource(
        &heapProps,
        D3D12_HEAP_FLAG_NONE,
        &resDesc,
        D3D12_RESOURCE_STATE_UNORDERED_ACCESS,
        nullptr,
        IID_PPV_ARGS(&resource)
    );
    assert(SUCCEEDED(hr));
    resources_.push_back(resource);

    // 初期データがある場合
    if (createInitialData && initialData) {
        Microsoft::WRL::ComPtr<ID3D12Resource> uploadBuffer;
        CD3DX12_HEAP_PROPERTIES uploadHeap(D3D12_HEAP_TYPE_UPLOAD);
        CD3DX12_RESOURCE_DESC uploadDesc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

        hr = device->CreateCommittedResource(
            &uploadHeap,
            D3D12_HEAP_FLAG_NONE,
            &uploadDesc,
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&uploadBuffer)
        );
        assert(SUCCEEDED(hr));

        void* mapped = nullptr;
        uploadBuffer->Map(0, nullptr, &mapped);
        memcpy(mapped, initialData, bufferSize);
        uploadBuffer->Unmap(0, nullptr);

        auto cmdList = CommandManager::GetInstance()->GetCommands().List;
        cmdList->CopyResource(resource.Get(), uploadBuffer.Get());
    }

    // UAV生成
    uavHandle_ = DescriptorManager::GetInstance()->AllocateUAV();

    D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc{};
    uavDesc.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
    uavDesc.Format = DXGI_FORMAT_UNKNOWN;
    uavDesc.Buffer.NumElements = elementCount;
    uavDesc.Buffer.StructureByteStride = sizeof(T);
    uavDesc.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_NONE;

    device->CreateUnorderedAccessView(resource.Get(), nullptr, &uavDesc, uavHandle_.cpuHandle);
}


/// <summary>
/// バインド
/// </summary>
template<typename T>
inline void RWStructuredBufferResource<T>::BindUAV(UINT rootParamIndex) const
{
    auto cmd = CommandManager::GetInstance()->GetCommands();
    cmd.List->SetComputeRootDescriptorTable(rootParamIndex, uavHandle_.gpuHandle);
}
