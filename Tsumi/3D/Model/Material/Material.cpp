#include "Material.h"



// 作成
void MaterialModel::Create()
{
	CreateBuffer();
	name = "default";
	textureHandle = 0;
	materialData.color = Vector4::one;
	materialData.uvTransform = Matrix4x4::identity;
	TransferMaterial();
}


// バッファ作成
void MaterialModel::CreateBuffer()
{
	CreateResource::CreateBufferResource(sizeof(MaterialDataN), constBuffer);

	// constBuffer が nullptr の場合はエラーログを出力してアサーションでプログラムを停止させる
	if (!constBuffer) {
		assert(false && "Failed to create constBuffer.");
	}
}


// マッピングする
void MaterialModel::Map()
{
	// constBuffer が nullptr の場合はエラーハンドリング
	if (!constBuffer) {
		// エラーログなどを出力するか、適切な対処を行う
		// この例ではエラーログを出力し、アサーションでプログラムを停止させる
		assert(false && "constBuff_ is nullptr. Make sure to create constBuffer before calling Map.");
		return;
	}

	HRESULT result = constBuffer->Map(0, nullptr, reinterpret_cast<void**>(&constMap));
	assert(SUCCEEDED(result));
}


// マッピング終了
void MaterialModel::UnMap()
{
	constBuffer->Unmap(0, nullptr);
}


// マテリアルの転送
void MaterialModel::TransferMaterial()
{
	Map();
	constMap->color = materialData.color;
	constMap->uvTransform = materialData.uvTransform;
	UnMap();
}
