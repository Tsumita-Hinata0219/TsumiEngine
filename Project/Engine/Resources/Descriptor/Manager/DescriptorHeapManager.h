#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <vector>
#include "../Handle/DescriptorHandle.h"

/* 各種ヒープ（SRV/CBV/UAV/RTV/DSV）を生成・割当 */
class DescriptorHeapManager {
public:
    enum class Type {
        SRV_CBV_UAV,
        RTV,
        DSV,
        Count
    };

    /// <summary>
    /// 初期化処理
    /// </summary>
    void Init(ID3D12Device* device);

    /// <summary>
    /// 指定したタイプのハンドルを1つ割り当てる
    /// </summary>
    DescriptorHandle Allocate(Type type);

    /// <summary>
    /// ヒープの取得
    /// </summary>
    ID3D12DescriptorHeap* GetHeap(Type type) const;

    /// <summary>
    /// サイズの取得
    /// </summary>
    UINT GetDescriptorSize(Type type) const;

private:
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heaps_[(int)Type::Count];
    UINT descriptorSizes_[(int)Type::Count]{};
    UINT currentOffsets_[(int)Type::Count]{};
};