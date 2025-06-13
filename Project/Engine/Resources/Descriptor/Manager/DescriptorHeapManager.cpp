#include "DescriptorHeapManager.h"
#include <cassert>
#include "DescriptorAllocator.h"


/// <summary>
/// 初期化処理
/// </summary>
void DescriptorHeapManager::Init(ID3D12Device* device) 
{
    assert(device);

    D3D12_DESCRIPTOR_HEAP_DESC heapDescs[(int)Type::Count] = {};

    heapDescs[(int)Type::SRV_CBV_UAV] = {
        .Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
        .NumDescriptors = 1024,
        .Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE
    };

    heapDescs[(int)Type::RTV] = {
        .Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
        .NumDescriptors = 256,
        .Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE
    };

    heapDescs[(int)Type::DSV] = {
        .Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV,
        .NumDescriptors = 256,
        .Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE
    };

    for (int i = 0; i < (int)Type::Count; ++i) {
        HRESULT hr = device->CreateDescriptorHeap(&heapDescs[i], IID_PPV_ARGS(&heaps_[i]));
        assert(SUCCEEDED(hr));
        descriptorSizes_[i] = device->GetDescriptorHandleIncrementSize(heapDescs[i].Type);
        currentOffsets_[i] = 0;
    }
}


/// <summary>
/// 指定したタイプのハンドルを1つ割り当てる
/// </summary>
DescriptorHandle DescriptorHeapManager::Allocate(Type type)
{
    UINT index = currentOffsets_[(int)type];
    currentOffsets_[(int)type]++;

    D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = heaps_[(int)type]->GetCPUDescriptorHandleForHeapStart();
    D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = heaps_[(int)type]->GetGPUDescriptorHandleForHeapStart();

    cpuHandle.ptr += index * descriptorSizes_[(int)type];
    gpuHandle.ptr += index * descriptorSizes_[(int)type];

    return DescriptorHandle(cpuHandle, gpuHandle, index);
}


/// <summary>
/// ヒープの取得
/// </summary>
ID3D12DescriptorHeap* DescriptorHeapManager::GetHeap(Type type) const
{
    return heaps_[(int)type].Get();
}


/// <summary>
/// サイズの取得
/// </summary>
UINT DescriptorHeapManager::GetDescriptorSize(Type type) const
{
    return descriptorSizes_[(int)type];
}
