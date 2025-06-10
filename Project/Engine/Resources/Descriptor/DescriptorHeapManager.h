#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <vector>
#include "DescriptorHandle.h"

/* 各種ヒープ（SRV/CBV/UAV/RTV/DSV）を生成・割当 */
class DescriptorHeapManager {
public:
    enum class Type {
        SRV_CBV_UAV,
        RTV,
        DSV,
        Count
    };

    void Initialize(ID3D12Device* device);
    DescriptorHandle Allocate(Type type);

    ID3D12DescriptorHeap* GetHeap(Type type) const;

    UINT GetDescriptorSize(Type type) const;

private:
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heaps_[(int)Type::Count];
    UINT descriptorSizes_[(int)Type::Count]{};
    UINT currentOffsets_[(int)Type::Count]{};
};