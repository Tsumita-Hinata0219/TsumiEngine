#pragma once
#include <queue>
#include <cstdint>
#include "../Handle/DescriptorHandle.h"
#include "../Manager/DescriptorHeapManager.h"

/* ヒープを管理 */
class DescriptorAllocator {

public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    DescriptorAllocator(DescriptorHeapManager& heapMgr, DescriptorHeapManager::Type type);

    /// <summary>
    /// 空きがあれば再利用。なければ新規確保
    /// </summary>
    DescriptorHandle Allocate();

    /// <summary>
    /// 解放されたインデックスを再利用待ちに追加
    /// </summary>
    void Free(UINT index);

    /// <summary>
    /// 全解放
    /// </summary>
    void Reset();

private:
    DescriptorHeapManager& heapManager_;
    DescriptorHeapManager::Type type_;
    std::queue<UINT> freeIndices_;
    UINT currentIndex_ = 0;
};