#pragma once
#include <wrl/client.h>
#include <d3d12.h>
#include <d3dx12.h>

/* リソースの基底クラス */
class IBaseResource {

public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    BaseResource() = default;

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~BaseResource() = default;

    /// <summary>
    /// リソースの生成（デバイスやデータに応じてオーバーライド）
    /// </summary>
    virtual bool Create(ID3D12Device* device) = 0;

    /// <summary>
    /// DescriptorHeapManagerを使ってSRVやCBVのDescriptorを作る処理もここで行うイメージ
    /// </summary>
    virtual void CreateDescriptors() = 0;

    /// <summary>
    /// リソースのアクセス用ハンドル（例：SRVハンドル）
    /// </summary>
    virtual D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle() const = 0;

protected:

    Microsoft::WRL::ComPtr<ID3D12Resource> resource_;

};