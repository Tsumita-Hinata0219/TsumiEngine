#include "TextureManager.h"



/// <summary>
/// 初期化処理
/// </summary>
void TextureManager::Initialize() {

	CoInitializeEx(0, COINIT_MULTITHREADED);
}



/// <summary>
/// 解放処理
/// </summary>
void TextureManager::Finalize() {

	CoUninitialize();

	// コンテナ内のResourceを削除
	UnLoadTexture();
}



/// <summary>
/// Textuerデータを読み込む
/// </summary>
uint32_t TextureManager::LoadTexture(const std::string& filePath, const std::string& FileName, TextureFrom from) 
{
	// インスタンスの取得
	TextureManager* instance = TextureManager::GetInstance();

	std::string fullFilePath{};

	switch (from)
	{
	case TextureFrom::Texture:
		fullFilePath = "Resources/Texture/" + filePath + "/" + FileName;
		break;
	case TextureFrom::Obj:
		fullFilePath = "Resources/Obj/" + filePath + "/" + FileName;
		break;
	case TextureFrom::gLTF:
		fullFilePath = "Resources/gLTF/" + filePath + "/" + FileName;
		break;
	default:
		break;
	}

	// マップコンテナで検索
	if (!instance->CheckTextureData(FileName)) {

		// なければ新しく作る
		instance->CreateTextureData(fullFilePath, FileName);
	}


	// filePahtのマップコンテナのindexを返す
	return instance->textureMaps_[FileName].index;
}



/// <summary>
/// Textureデータの解放
/// </summary>
void TextureManager::UnLoadTexture() {

	TextureManager::GetInstance()->textureMaps_.clear();
}



/// <summary>
/// 一回読み込んだものは読み込まない
/// </summary>
bool TextureManager::CheckTextureData(std::string key) {

	// マップコンテナに検索をかける
	auto data = textureMaps_.find(key);

	// ヒットしたらtrueを返す
	if (data != textureMaps_.end()) {
		return true;
	}
	return false;
}


/// <summary>
/// TextureDataを生成する
/// </summary>
void TextureManager::CreateTextureData(std::string fullFilePath, std::string key)
{
	// インスタンスの取得
	TextureManager* instance = TextureManager::GetInstance();

	// 新しく作成するTextureDataを用意
	TextureData textureData{};

	// Textureを読んで転送する
	DirectX::ScratchImage mipImages = CreateMipImage(fullFilePath);
	const DirectX::TexMetadata& metadata = mipImages.GetMetadata();
	textureData.resource = CreateTextureResource(metadata);

	// 登録
	UpdateTextureData(metadata, mipImages, textureData);

	// SRV作成
	textureData.index = SRVManager::CreateTextureSRV(textureData.resource, metadata);

	// textureのサイズの取得
	textureData.size = {
		static_cast<float>(metadata.width),
		static_cast<float>(metadata.height) };

	// コンテナに保存
	instance->textureMaps_[key] = textureData;
}




/// <summary>
/// Textureファイルを開く
/// </summary>
DirectX::ScratchImage TextureManager::CreateMipImage(const std::string& filePath) {

	// テクスチャファイルを読み込んでプログラムで扱えるようにする
	// Textureデータを読み込む
	DirectX::ScratchImage image{};
	std::wstring filePathw = ConverString(filePath);
	HRESULT hr = DirectX::LoadFromWICFile(filePathw.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image);
	assert(SUCCEEDED(hr));

	// ミニマップの作成
	DirectX::ScratchImage mipImages{};
	hr = DirectX::GenerateMipMaps(
		image.GetImages(), image.GetImageCount(), image.GetMetadata(),
		DirectX::TEX_FILTER_SRGB, 0, mipImages);
	assert(SUCCEEDED(hr));

	// ミニマップ付きのデータを探す	
	return mipImages;
}



/// <summary>
/// DirectX12のTExtureResourceを作る
/// </summary>
ComPtr<ID3D12Resource> TextureManager::CreateTextureResource(const DirectX::TexMetadata& metadata) {

	// 1.metadataを基にResourceの設定
	// metadataを基にResourceの設定
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc = SettingResource(metadata);

	// 2. 利用するHeapの設定
	// 利用するHeapの設定。非常に特殊な運用 ※02_04exで一般的なケース版がある
	D3D12_HEAP_PROPERTIES heapProperties{};
	heapProperties = SettingUseHeap();

	// 3. Resourceを作る
	// Resourceを生成する
	ComPtr<ID3D12Resource> resource{};
	resource = CreateResource(resourceDesc, heapProperties);

	return resource;
}



/// <summary>
/// metadataを基にResourceの設定
/// </summary>
D3D12_RESOURCE_DESC TextureManager::SettingResource(const DirectX::TexMetadata& metadata) {

	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Width = UINT(metadata.width);								// Textureの幅
	resourceDesc.Height = UINT(metadata.height);							// Textureの高さ
	resourceDesc.MipLevels = UINT16(metadata.mipLevels);						// mipmapの数
	resourceDesc.DepthOrArraySize = UINT16(metadata.arraySize);			    // 奥行き or 配列Textureの配列数
	resourceDesc.Format = metadata.format;									// TextureのFormat
	resourceDesc.SampleDesc.Count = 1;										// サンプリングカウント。1固定
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION(metadata.dimension);  // Textureの次元数。普段使っているのは2次元

	return resourceDesc;
}



/// <summary>
/// 利用するHeapの設定
/// </summary>
D3D12_HEAP_PROPERTIES TextureManager::SettingUseHeap() {

	D3D12_HEAP_PROPERTIES heapProperties{};
	heapProperties.Type = D3D12_HEAP_TYPE_CUSTOM;                        // 細かい設定を行う
	heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK; // WriteBackポリシーでCPUアクセス可能
	heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;	         // プロセッサの近くに配置

	return heapProperties;
}



/// <summary>
/// Resourceを生成する
/// </summary>
ComPtr<ID3D12Resource> TextureManager::CreateResource(D3D12_RESOURCE_DESC resourceDesc, D3D12_HEAP_PROPERTIES heapProperties) {

	ComPtr<ID3D12Resource> resource;
	HRESULT result;
	result = DirectXCommon::GetInstance()->GetDevice()->CreateCommittedResource(
		&heapProperties,				   // Heapの設定
		D3D12_HEAP_FLAG_NONE,			   // Heapの特殊な設定。特になし
		&resourceDesc,					   // Resourceの設定
		D3D12_RESOURCE_STATE_GENERIC_READ, // 初回のResourceState。Textureは基本読むだけ
		nullptr,						   // Clear最適地。使わないのでnullptr
		IID_PPV_ARGS(&resource));		   // 作成するResourceポインタへのポインタ
	assert(SUCCEEDED(result));

	return resource;
}



/// <summary>
/// TextureResourceにデータを転送する
/// </summary>
void TextureManager::UpdateTextureData(const DirectX::TexMetadata& metadata, DirectX::ScratchImage& mipImages, TextureData textureData) {

	// Meta情報を取得
	//const DirectX::TexMetadata& metadata = mipImage.GetMetadata();

	// 全MipMapについて
	for (size_t mipLevel = 0; mipLevel < metadata.mipLevels; ++mipLevel) {

		//MipMapLevelを指定して各Imageを取得
		const DirectX::Image* img = mipImages.GetImage(mipLevel, 0, 0);

		// Textureに転送
		HRESULT result;
		result = textureData.resource->WriteToSubresource(
			UINT(mipLevel),
			nullptr,			  // 全領域へコピー
			img->pixels,		  // 元データアドレス
			UINT(img->rowPitch),  // 1ラインサイズ
			UINT(img->slicePitch) // 1枚サイズ
		);
		assert(SUCCEEDED(result));
	}
}

