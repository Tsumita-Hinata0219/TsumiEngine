#include "DescriptorAllocator.h"
#include <cassert>


/// <summary>
/// コンストラクタ
/// </summary>
DescriptorAllocator::DescriptorAllocator()
    : type_(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV),
    baseCPU_({}),
    baseGPU_({}),
    descriptorSize_(0),
    maxDescriptors_(0),
    currentIndex_(0) {
}


/// <summary>
/// 初期化
/// </summary>
void DescriptorAllocator::Init(D3D12_DESCRIPTOR_HEAP_TYPE type, D3D12_CPU_DESCRIPTOR_HANDLE baseCPU, D3D12_GPU_DESCRIPTOR_HANDLE baseGPU, UINT descriptorSize, UINT maxDescriptors)
{
    type_ = type;
    baseCPU_ = baseCPU;
    baseGPU_ = baseGPU;
    descriptorSize_ = descriptorSize;
    maxDescriptors_ = maxDescriptors;
    currentIndex_ = 0;
}


/// <summary>
/// 次のディスクリプタを割り当てて返す（インクリメント）
/// </summary>
D3D12_CPU_DESCRIPTOR_HANDLE DescriptorAllocator::AllocateCPUHandle()
{
    if (currentIndex_ >= maxDescriptors_) {
        throw std::runtime_error("DescriptorAllocator: Exceeded descriptor heap size!");
    }

    D3D12_CPU_DESCRIPTOR_HANDLE handle = baseCPU_;
    handle.ptr += descriptorSize_ * currentIndex_;
    return handle;
}

D3D12_GPU_DESCRIPTOR_HANDLE DescriptorAllocator::AllocateGPUHandle()
{
    if (currentIndex_ >= maxDescriptors_) {
        throw std::runtime_error("DescriptorAllocator: Exceeded descriptor heap size!");
    }

    D3D12_GPU_DESCRIPTOR_HANDLE handle = baseGPU_;
    handle.ptr += descriptorSize_ * currentIndex_;
    ++currentIndex_;
    return handle;
}


/// <summary>
/// リセットして再利用（フレームバッファなどに）
/// </summary>
void DescriptorAllocator::Reset() 
{
	currentIndex_ = 0;
}