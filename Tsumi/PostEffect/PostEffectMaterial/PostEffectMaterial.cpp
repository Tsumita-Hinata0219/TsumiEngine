#include "PostEffectMaterial.h"



// マテリアル作成
void PostEffectMaterial::Create()
{
	CreateBuffer();
	mtlData.color = Vector4::one;
	TransferMaterial();
}


// マテリアルの転送
void PostEffectMaterial::TransferMaterial()
{
	Map();
	constMap->color = mtlData.color;
	UnMap();
}


// バッファ作成
void PostEffectMaterial::CreateBuffer()
{
	CreateResource::CreateBufferResource(sizeof(PostEffectMtlData), constBuffer);

	// constBuffer が nullptr の場合はエラーログを出力してアサーションでプログラムを停止させる
	if (!constBuffer) {
		assert(false && "Failed to create constBuffer.");
	}
}


// マッピングする
void PostEffectMaterial::Map()
{
	// constBuffer が nullptr の場合はエラーハンドリング
	if (!constBuffer) {
		// エラーログを出力し、アサーションでプログラムを停止させる
		assert(false && "constBuff_ is nullptr. Make sure to create constBuffer before calling Map.");
		return;
	}

	HRESULT result = constBuffer->Map(0, nullptr, reinterpret_cast<void**>(&constMap));
	assert(SUCCEEDED(result));
}


// マッピング終了
void PostEffectMaterial::UnMap()
{
	constBuffer->Unmap(0, nullptr);
}