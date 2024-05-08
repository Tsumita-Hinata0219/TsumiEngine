#include "Material.h"



// 作成
void Material::Create()
{
	name = "default";
	textureHandle = 0;
	materialData.color = Vector4::one;
	materialData.uvTransform = Matrix4x4::identity;
}


// バッファ作成
void Material::CreateBuffer()
{
	Map();
	constMap->color = materialData.color;
	constMap->uvTransform = materialData.uvTransform;
	UnMap();
}


// マッピングする
void Material::Map() 
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
void Material::UnMap()
{
	constBuffer->Unmap(0, nullptr);
}