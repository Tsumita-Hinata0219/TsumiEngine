#pragma once

#include <string>
#include <wrl.h>
#include <d3d12.h>
#include <cassert>
#include <vector>


/* リソースの基底クラス */
class BaseResurce {

public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    BaseResurce() = default;

    /// <summary>
    /// 仮想デストラクタ
    /// </summary>
    virtual ~BaseResurce() = default;

    /// <summary>
    /// リソースを設定
    /// </summary>
    void SetResource(Microsoft::WRL::ComPtr<ID3D12Resource> resource);

    /// <summary>
    /// 名前を付ける
    /// </summary>
    void SetName(const std::wstring& name);

    /// <summary>
    /// GPU仮想アドレスを取得
    /// </summary>
    D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress() const;

    /// <summary>
    /// サイズを設定
    /// </summary>
    void SetSize(UINT size);

    /// <summary>
    /// サイズを取得
    /// </summary>
    UINT GetSize() const;

    /// <summary>
    /// リソース本体を取得
    /// </summary>
    ID3D12Resource* GetResource() const { return resource_.Get(); }

protected:

    Microsoft::WRL::ComPtr<ID3D12Resource> resource_;
    std::wstring name_;
    UINT size_ = 0;
};