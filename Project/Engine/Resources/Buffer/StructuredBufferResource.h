#pragma once
#include "../Base/BaseResource.h"
#include "../../Graphics/CommandManager/CommandManager.h"
#include "../Descriptor/Allocator/DescriptorAllocator.h"


/* 読み取り専用バッファ(SRV) */
template<typename T>
class StructuredBufferResource : public BaseResurce {

public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    StructuredBufferResource();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~StructuredBufferResource();

    /// <summary>
    /// 生成
    /// </summary>
    void Create(const std::vector<T>& data);

    /// <summary>
    /// バインド
    /// </summary>
    void Bind(UINT rootParamIndex) const;

    /// <summary>
    /// GPUHandleの取得
    /// </summary>
    D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle() const { return srvHandle_.gpuHandle; }

private:
    std::vector<T> bufferData_;
    DescriptorHandle srvHandle_;
};



/// <summary>
/// コンストラクタ
/// </summary>
template<typename T>
inline StructuredBufferResource<T>::StructuredBufferResource() {}


/// <summary>
/// デストラクタ
/// </summary>
template<typename T>
inline StructuredBufferResource<T>::~StructuredBufferResource() {}


/// <summary>
/// 生成
/// </summary>
template<typename T>
inline void StructuredBufferResource<T>::Create(const std::vector<T>& data)
{
    bufferData_ = data;
    UINT bufferSize = static_cast<UINT>(sizeof(T) * data.size());

    auto device = DirectXManager::GetInstance()->GetDevice();
    CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);
    CD3DX12_RESOURCE_DESC resDesc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);
    resDesc.StructureByteStride = sizeof(T);
    resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

    Microsoft::WRL::ComPtr<ID3D12Resource> res;
    HRESULT hr = device->CreateCommittedResource(
        &heapProps,
        D3D12_HEAP_FLAG_NONE,
        &resDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&res)
    );
    assert(SUCCEEDED(hr));
    resources_.push_back(res);

    void* mapped = nullptr;
    res->Map(0, nullptr, &mapped);
    std::memcpy(mapped, data.data(), bufferSize);
    res->Unmap(0, nullptr);

    // SRV作成
    srvHandle_ = DescriptorManager::GetInstance()->AllocateSRV();

    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
    srvDesc.Format = DXGI_FORMAT_UNKNOWN;
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srvDesc.Buffer.NumElements = static_cast<UINT>(data.size());
    srvDesc.Buffer.StructureByteStride = sizeof(T);
    srvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;

    device->CreateShaderResourceView(res.Get(), &srvDesc, srvHandle_.cpuHandle);
}


/// <summary>
/// バインド
/// </summary>
template <typename T>
inline void StructuredBufferResource<T>::Bind(UINT rootParamIndex) const
{
    auto cmd = CommandManager::GetInstance()->GetCommands();
    cmd.List->SetGraphicsRootDescriptorTable(rootParamIndex, srvHandle_.gpuHandle);
}
