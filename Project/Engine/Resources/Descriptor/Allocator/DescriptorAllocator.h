#pragma once
#include <queue>
#include <cstdint>
#include <d3d12.h>
#include <wrl.h>
#include <vector>
#include <unordered_map>
#include <mutex>
#include "../Handle/DescriptorHandle.h"
#include "../Manager/DescriptorHeapManager.h"


/* SRV/UAV/RTV/DSVのディスクリプタヒープをタイプごとに別々に管理する */
class DescriptorAllocator {

public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    DescriptorAllocator();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~DescriptorAllocator() = default;

    /// <summary>
    /// 初期化
    /// </summary>
    void Init(
        D3D12_DESCRIPTOR_HEAP_TYPE type,
        D3D12_CPU_DESCRIPTOR_HANDLE baseCPU,
        D3D12_GPU_DESCRIPTOR_HANDLE baseGPU,
        UINT descriptorSize,
        UINT maxDescriptors);

    /// <summary>
    /// 次のディスクリプタを割り当てて返す（インクリメント）
    /// </summary>
    D3D12_CPU_DESCRIPTOR_HANDLE AllocateCPUHandle();
    D3D12_GPU_DESCRIPTOR_HANDLE AllocateGPUHandle();

    /// <summary>
    /// 現在のインデックスを返す（デバッグ・SRV登録用）
    /// </summary>
    UINT GetCurrentIndex() const { return currentIndex_; }

    /// <summary>
    /// リセットして再利用（フレームバッファなどに）
    /// </summary>
    void Reset();

private:
    D3D12_DESCRIPTOR_HEAP_TYPE type_;
    D3D12_CPU_DESCRIPTOR_HANDLE baseCPU_;
    D3D12_GPU_DESCRIPTOR_HANDLE baseGPU_;
    UINT descriptorSize_;
    UINT maxDescriptors_;
    UINT currentIndex_;
};