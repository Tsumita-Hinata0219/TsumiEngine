#include "Mesh.h"



// メッシュ作成
void Mesh::Create()
{
	CreateBuffer();
	name = "deafult";
	TransferMesh();
}

// バッファ作成
void Mesh::CreateBuffer()
{
	CreateResource::CreateBufferResource(sizeof(MeshData), constBuffer);

	// constBuffer が nullptr の場合はエラーログを出力してアサーションでプログラムを停止させる
	if (!constBuffer) {
		assert(false && "Failed to create constBuffer.");
	}
}


// マッピングする
void Mesh::Map()
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
void Mesh::UnMap()
{
	constBuffer->Unmap(0, nullptr);
}


// メッシュの転送
void Mesh::TransferMesh()
{
	Map();
	constMap->vertices = meshData.vertices;
	constMap->rootNode = meshData.rootNode;
	UnMap();
}