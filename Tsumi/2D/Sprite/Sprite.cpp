#include "Sprite.h"



/// <summary>
/// 初期化処理
/// </summary>
void Sprite::Initialize(Vector2 pos, Vector2 size) {

	// 初期座標の設定
	pos_ = pos;

	// サイズの設定
	size_ = size;

	// uvTransformの設定
	uvTransform_ = {
		{ 1.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
	};

	// テクスチャの設定
	// デフォルトではuvCheckerを使う
	useTexture_ = 1;

	// 色の設定
	color_ = { 1.0f, 1.0f, 1.0f, 1.0f };

	// リソースの作成
	resource_.Vertex = CreateResource::CreateBufferResource(sizeof(VertexData) * 4);
	resource_.Material = CreateResource::CreateBufferResource(sizeof(MaterialSprite));
	resource_.VertexBufferView = CreateResource::CreateVertexBufferView(sizeof(VertexData) * 4, resource_.Vertex.Get(), 4);

	resource_.Index = CreateResource::CreateBufferResource(sizeof(uint32_t) * 6);
	resource_.IndexBufferView = CreateResource::CreateIndexBufferview(sizeof(uint32_t) * 6, resource_.Index.Get());
}


/// <summary>
/// 描画処理
/// </summary>
void Sprite::Draw(uint32_t texHandle, WorldTransform& worldTransform, ViewProjection view) {

	// 頂点データを設定する
	SetVertex(worldTransform);

	// RootSignatureを設定。
	DirectXCommon::GetInstance()->GetCommandList()->SetGraphicsRootSignature(SpriteGraphicPipeline::GetInstance()->GetPsoProperty().rootSignature);
	// PSOを設定
	DirectXCommon::GetInstance()->GetCommandList()->SetPipelineState(SpriteGraphicPipeline::GetInstance()->GetPsoProperty().graphicsPipelineState);

	// 頂点の設定
	DirectXCommon::GetInstance()->GetCommandList()->IASetVertexBuffers(0, 1, &resource_.VertexBufferView); // VBVを設定
	DirectXCommon::GetInstance()->GetCommandList()->IASetIndexBuffer(&resource_.IndexBufferView);

	// 形状を設定
	DirectXCommon::GetInstance()->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Material用のCBufferの場所を設定
	DirectXCommon::GetInstance()->GetCommandList()->SetGraphicsRootConstantBufferView(0, resource_.Material->GetGPUVirtualAddress());

	// wvp用のCBufferの場所を設定
	DirectXCommon::GetInstance()->GetCommandList()->SetGraphicsRootConstantBufferView(1, worldTransform.constBuffer->GetGPUVirtualAddress());

	// View用のCBufferの場所を設定
	DirectXCommon::GetInstance()->GetCommandList()->SetGraphicsRootConstantBufferView(2, view.constBuffer->GetGPUVirtualAddress());

	// DescriptorTableを設定する
	if (!texHandle == 0) {
		DescriptorManager::SetGraphicsRootDescriptorTable(3, texHandle);
	}

	// 描画！(DrawCall/ドローコール)
	DirectXCommon::GetInstance()->GetCommandList()->DrawIndexedInstanced(6, 1, 0, 0, 0);
}



/// <summary>
/// 頂点データを設定する
/// </summary>
void Sprite::SetVertex(WorldTransform worldTransform) {

	VertexData* vertexData = nullptr;
	MaterialSprite* materialData = nullptr;
	uint32_t* indexData = nullptr;

	// 書き込みができるようにする
	resource_.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	resource_.Material->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	resource_.Index->Map(0, nullptr, reinterpret_cast<void**>(&indexData));

	pos_ = { 
		worldTansform_.translate.x, 
		worldTansform_.translate.y };

	// 左下
	vertexData[0].position = { pos_.x, pos_.y + size_.y, 0.0f, 1.0f };
	vertexData[0].texCoord = { 0.0f, 1.0f };

	// 左上
	vertexData[1].position = { pos_.x, pos_.y, 0.0f, 1.0f };
	vertexData[1].texCoord = { 0.0f, 0.0f };


	// 右下
	vertexData[2].position = { pos_.x + size_.x, pos_.y + size_.y, 0.0f, 1.0f };
	vertexData[2].texCoord = { 1.0f, 1.0f };
	
	// 右上
	vertexData[3].position = { pos_.x + size_.x, pos_.y, 0.0f, 1.0f };
	vertexData[3].texCoord = { 1.0f, 0.0f };


	indexData[0] = 0; indexData[1] = 1; indexData[2] = 2;
	indexData[3] = 1; indexData[4] = 3; indexData[5] = 2;


	materialData->color = color_;
	materialData->uvTransform = MakeAffineMatrix(uvTransform_.scale, uvTransform_.rotate, uvTransform_.translate);
}


/// <summary>
/// 色の変換
/// </summary>
Vector4 Sprite::FloatColor(unsigned int color) {

	Vector4 colorf = {
		((color >> 24) & 0xff) / 255.0f, // R
		((color >> 16) & 0xff) / 255.0f, // G
		((color >> 8) & 0xff) / 255.0f,  // B
		((color >> 0) & 0xff) / 255.0f   // A
	};

	return colorf;
}