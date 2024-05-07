#include "PostEffect.h"



// 初期化処理
void PostEffect::Initialize()
{

	// リソースの作成
	resource_.Vertex = CreateResource::CreateBufferResource(sizeof(VertexData) * 3);
	resource_.Material = CreateResource::CreateBufferResource(sizeof(Material));
	resource_.VertexBufferView = CreateResource::CreateVertexBufferView(sizeof(VertexData) * 3, resource_.Vertex.Get(), 3);

	//srv_ = DescriptorManager::CreateRenderTextureSRV(resource_.Vertex);
}


// 描画処理
void PostEffect::Draw()
{
	VertexData* vertexData = nullptr;
	Material* materialData = nullptr;

	// 書き込みができるようにする
	resource_.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	resource_.Material->Map(0, nullptr, reinterpret_cast<void**>(&materialData));

	// 頂点の設定

	//// 左上
	//vertexData[0].position = { pos_.x, pos_.y, 0.0f, 1.0f };
	//vertexData[0].texCoord = { 0.0f, 0.0f };

	//// 右上
	//vertexData[1].position = { pos_.x + size_.x, pos_.y, 0.0f, 1.0f };
	//vertexData[1].texCoord = { 1.0f, 0.0f };

	//// 左下
	//vertexData[2].position = { pos_.x, pos_.y + size_.y, 0.0f, 1.0f };
	//vertexData[2].texCoord = { 0.0f, 1.0f };


	// 色
	materialData->color = Vector4::one;


	// コマンドコール
	CommandCall();
}


// コマンドコール
void PostEffect::CommandCall()
{
	// コマンドの取得
	Commands commands = DirectXCommon::GetInstance()->GetCommands();

	// RootSignatureの設定
	commands.List->SetGraphicsRootSignature(PostEffectGraphicPipeline::GetInstance()->GetPsoProperty().rootSignature);

	// PSOの設定
	commands.List->SetPipelineState(PostEffectGraphicPipeline::GetInstance()->GetPsoProperty().graphicsPipelineState);

	// 形状の設定
	commands.List->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 頂点の設定
	commands.List->IASetVertexBuffers(0, 1, &resource_.VertexBufferView);

	// Materialの設定
	commands.List->SetGraphicsRootConstantBufferView(0, resource_.Material->GetGPUVirtualAddress());

	// DescriptorTableの設定
	DescriptorManager::SetGraphicsRootDescriptorTable(3, srv_);

	// 頂点3つ描画
	commands.List->DrawInstanced(3, 1, 0, 0);
}
