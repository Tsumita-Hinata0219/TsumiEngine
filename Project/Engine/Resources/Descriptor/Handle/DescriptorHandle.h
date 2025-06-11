#pragma once
#include <d3d12.h>

/* CPU/GPU ハンドル＋Indexをまとめて持つ構造体 */
struct DescriptorHandle {

    D3D12_CPU_DESCRIPTOR_HANDLE CPU{};
    D3D12_GPU_DESCRIPTOR_HANDLE GPU{};
    UINT Index = 0;

    /// <summary>
    /// コンストラクタ 
    /// </summary>
    DescriptorHandle() = default;
    DescriptorHandle(D3D12_CPU_DESCRIPTOR_HANDLE cpu, D3D12_GPU_DESCRIPTOR_HANDLE gpu, UINT index)
        : CPU(cpu), GPU(gpu), Index(index) {
    }
};