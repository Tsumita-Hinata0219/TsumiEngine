#pragma once
#include "../Base/Resourcebase.h"
#include "../Descriptor/Allocator/DescriptorAllocator.h"
#include "../../Graphics/CommandManager/CommandManager.h"
#include <d3d12.h>
#include <wrl.h>


/* 定数バッファクラス */
template <typename T>
class ConstantoBufferResource : public BaseResurce {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ConstantoBufferResource(DescriptorAllocator& allocator);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ConstantoBufferResource();

	/// <summary>
	/// 生成
	/// </summary>
	void Create(UINT itemCount = 1);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(const T* data, UINT index = 0);

	/// <summary>
	/// バインド
	/// </summary>
	void Bind(UINT rootParameterIndex, UINT index = 0);

	/// <summary>
	/// データ取得
	/// </summary>
	T* GetMappedData(UINT index = 0) const { return mappedData_[index]; }


private:

	DescriptorAllocator& allocator_;
	std::vector<D3D12_GPU_VIRTUAL_ADDRESS> gpuAddresses_;
	std::vector<T*> mappedData_;
	std::vector<DescriptorHandle> cbvHandles_;
	UINT itemCount_ = 0;

};



/// <summary>
/// コンストラクタ
/// </summary>
template<typename T>
inline ConstantoBufferResource<T>::ConstantoBufferResource(DescriptorAllocator& allocator)
	: allocator_(allocator) {}


/// <summary>
/// デストラクタ
/// </summary>
template<typename T>
inline ConstantoBufferResource<T>::~ConstantoBufferResource() {}


/// <summary>
/// 生成
/// </summary>
template<typename T>
inline void ConstantoBufferResource<T>::Create(UINT itemCount)
{
    itemCount_ = itemCount;
    gpuAddresses_.resize(itemCount_);
    mappedData_.resize(itemCount_);
    cbvHandles_.resize(itemCount_);

    UINT size = (sizeof(T) + 255) & ~255;  // CBV は 256バイトアライメント

    for (UINT i = 0; i < itemCount_; ++i) {
        CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);
        CD3DX12_RESOURCE_DESC resDesc = CD3DX12_RESOURCE_DESC::Buffer(size);

        ComPtr<ID3D12Resource> res;
        HRESULT hr = DirectXManager::GetInstance()->GetDevice()->CreateCommittedResource(
            &heapProps,
            D3D12_HEAP_FLAG_NONE,
            &resDesc,
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&res)
        );
        assert(SUCCEEDED(hr));

        resources_.push_back(res);

        // マッピング
        void* mapped = nullptr;
        res->Map(0, nullptr, &mapped);
        mappedData_[i] = reinterpret_cast<T*>(mapped);
        gpuAddresses_[i] = res->GetGPUVirtualAddress();

        // CBV作成
        D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc{};
        cbvDesc.BufferLocation = gpuAddresses_[i];
        cbvDesc.SizeInBytes = size;

        cbvHandles_[i] = allocator_.Allocate();
        DirectXManager::GetInstance()->GetDevice()->CreateConstantBufferView(
            &cbvDesc,
            cbvHandles_[i].CPU
        );
    }
}


/// <summary>
/// 更新処理
/// </summary>
template<typename T>
inline void ConstantoBufferResource<T>::Update(const T* data, UINT index)
{
    assert(index < itemCount_);
    std::memcpy(mappedData_[index], data, sizeof(T));
}


/// <summary>
/// バインド
/// </summary>
template<typename T>
inline void ConstantoBufferResource<T>::Bind(UINT rootParameterIndex, UINT index)
{
    Commands cmd = CommandManager::GetInstance()->GetCommands();
    ID3D12DescriptorHeap* heaps[] = {
        DirectXManager::GetInstance()->GetSrvDescriptorHeap()
    };
    cmd.List->SetDescriptorHeaps(1, heaps);
    cmd.List->SetGraphicsRootDescriptorTable(rootParameterIndex, cbvHandles_[index].GPU);
}
