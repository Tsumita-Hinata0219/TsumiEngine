#pragma once

#include "DirectXTex.h"
#include "../Base/DXCommon/DirectXCommon.h"
#include "../DescriptorManager/DescriptorManager.h"
#include "../View/SRVManager/SRVManager.h"
#include "TextureDataResource/TextureDataResource.h"
#include "../../Project/Math/MyMath.h"

#include <cassert>
#include <map>


enum class TextureFrom {
	Texture,
	Obj,
	gLTF,
};

class TextureManager {

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TextureManager() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TextureManager() {};

	/// <summary>
	/// TextureManagerのインスタンス取得
	/// </summary>
	static TextureManager* GetInstance();

	/// <summary>
	/// 初期化処理
	/// </summary>
	static void Initialize();

	/// <summary>
	/// 解放処理
	/// </summary>
	static void Finalize();

	/// <summary>
	/// Textuerデータを読み込む
	/// </summary>
	static uint32_t LoadTexture(const std::string& filePath, const std::string& fileName, TextureFrom from = TextureFrom::Texture);

	/// <summary>
	/// Textureデータの解放
	/// </summary>
	static void UnLoadTexture();


private: // メンバ関数

	/// <summary>
	/// 一回読み込んだものは読み込まない
	/// </summary>
	bool CheckTextureData(std::string key);

	/// <summary>
	/// TextureDataを生成する
	/// </summary>
	void CreateTextureData(std::string fullFilePath, std::string key);

	/// <summary>
	/// Textureファイルを開く
	/// </summary>
	static DirectX::ScratchImage CreateMipImage(const std::string& filePath);

	/// <summary>
	/// DirectX12のTextureResourceを作る
	/// </summary>
	static ComPtr<ID3D12Resource> CreateTextureResource(const DirectX::TexMetadata& metadata);

	/// <summary>
	/// TextureResourceにデータを転送する
	/// </summary>
	static void UpdateTextureData(const DirectX::TexMetadata& metadata, DirectX::ScratchImage& mipImages, TextureData textureData);

	/// <summary>
	/// metadataを基にResourceの設定
	/// </summary>
	static D3D12_RESOURCE_DESC SettingResource(const DirectX::TexMetadata& metadata);

	/// <summary>
	/// 利用するHeapの設定
	/// </summary>
	static D3D12_HEAP_PROPERTIES SettingUseHeap();

	/// <summary>
	/// Resourceを生成する
	/// </summary>
	static ComPtr<ID3D12Resource> CreateResource(D3D12_RESOURCE_DESC resourceDesc, D3D12_HEAP_PROPERTIES heapProperties);


private: // メンバ変数

	// テクスチャのコンテナマップ
	std::map < std::string, TextureData> textureMaps_;
};