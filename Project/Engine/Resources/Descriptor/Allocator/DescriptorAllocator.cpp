#include "DescriptorAllocator.h"



/// <summary>
/// コンストラクタ
/// </summary>
DescriptorAllocator::DescriptorAllocator(DescriptorHeapManager& heapMgr, DescriptorHeapManager::Type type)
	: heapManager_(heapMgr), type_(type), currentIndex_(0) {}


/// <summary>
/// 空きがあれば再利用。なければ新規確保
/// </summary>
DescriptorHandle DescriptorAllocator::Allocate()
{
    UINT index;

    if (!freeIndices_.empty()) {
        index = freeIndices_.front();
        freeIndices_.pop();
    }
    else {
        index = currentIndex_++;
    }

    D3D12_CPU_DESCRIPTOR_HANDLE cpu = heapManager_.GetHeap(type_)->GetCPUDescriptorHandleForHeapStart();
    D3D12_GPU_DESCRIPTOR_HANDLE gpu = heapManager_.GetHeap(type_)->GetGPUDescriptorHandleForHeapStart();
    UINT size = heapManager_.GetDescriptorSize(type_);

    cpu.ptr += index * size;
    gpu.ptr += index * size;

    return DescriptorHandle(cpu, gpu, index);
}


/// <summary>
/// 解放されたインデックスを再利用待ちに追加
/// </summary>
void DescriptorAllocator::Free(UINT index)
{
    freeIndices_.push(index);
}



/// <summary>
/// 全解放
/// </summary>
void DescriptorAllocator::Reset()
{
    while (!freeIndices_.empty()) {
        freeIndices_.pop();
    }
    currentIndex_ = 0;
}
