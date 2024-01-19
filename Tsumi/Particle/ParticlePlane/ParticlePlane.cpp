#include "ParticlePlane.h"
#include "Particle.h"


/// <summary>
/// 初期化処理
/// </summary>
void ParticlePlane::Initialize(Particle* pParticle) {

	pParticle;

	NumInstance_ = pParticle->GetInstanceNum();

	// リソースの作成
	resource_.Vertex = CreateResource::CreateBufferResource(sizeof(VertexData) * 4);
	resource_.Material = CreateResource::CreateBufferResource(sizeof(MaterialParticle));
	resource_.VertexBufferView = CreateResource::CreateVertexBufferView(sizeof(VertexData) * 4, resource_.Vertex.Get(), 4);

	resource_.Index = CreateResource::CreateBufferResource(sizeof(uint32_t) * 6);
	resource_.IndexBufferView = CreateResource::CreateIndexBufferview(sizeof(uint32_t) * 6, resource_.Index.Get());

	resource_.instancing = CreateResource::CreateBufferResource(sizeof(ParticleTransformationMatrix) * NumInstance_);
	dsvIndex_ = DescriptorManager::CreateInstancingSRV(NumInstance_, resource_.instancing, sizeof(ParticleTransformationMatrix));
}



/// <summary>
/// 描画処理
/// </summary>
void ParticlePlane::Draw(Particle* pParticle, list<ParticleProperties> prope, ViewProjection view) {

	VertexData* vertexData = nullptr;
	MaterialParticle* materialData = nullptr;
	uint32_t* indexData = nullptr;
	ParticleTransformationMatrix* instancingData = nullptr;

	// 書き込みができるようにする
	resource_.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	resource_.Material->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	resource_.Index->Map(0, nullptr, reinterpret_cast<void**>(&indexData));
	resource_.instancing->Map(0, nullptr, reinterpret_cast<void**>(&instancingData));


	// 左下
	vertexData[0].position = { pos_.x - size_, pos_.y - size_, pos_.z, 1.0f };
	vertexData[0].texCoord = { 0.0f, 1.0f };
	vertexData[0].normal = { 0.0f, 1.0f, 0.0f };

	// 左上
	vertexData[1].position = { pos_.x - size_, pos_.y + size_, pos_.z, 1.0f };
	vertexData[1].texCoord = { 0.0f, 0.0f };
	vertexData[1].normal = { 0.0f, 1.0f, 0.0f };

	// 右下
	vertexData[2].position = { pos_.x + size_, pos_.y - size_, pos_.z, 1.0f };
	vertexData[2].texCoord = { 1.0f, 1.0f };
	vertexData[2].normal = { 0.0f, 1.0f, 0.0f };

	// 右上
	vertexData[3].position = { pos_.x + size_, pos_.y + size_, pos_.z, 1.0f };
	vertexData[3].texCoord = { 1.0f, 0.0f };
	vertexData[3].normal = { 0.0f, 1.0f, 0.0f };


	// 頂点インデックス
	indexData[0] = 0; indexData[1] = 1; indexData[2] = 2;
	indexData[3] = 1; indexData[4] = 3; indexData[5] = 2;


	// マテリアルの設定
	materialData->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	materialData->uvTransform = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });


	itrNum_ = 0;
	for (auto itr = prope.begin(); itr != prope.end(); itr++) {

		Matrix4x4 worldPos = MakeAffineMatrix((*itr).worldTransform.scale, (*itr).worldTransform.rotate, (*itr).worldTransform.translate);
		Matrix4x4 worldView = view.matView * view.matProjection;
		Matrix4x4 matWorld = worldPos * worldView;

		(*itr).uvTransform.matWorld = MakeAffineMatrix(
			(*itr).uvTransform.scale, (*itr).uvTransform.rotate, (*itr).uvTransform.translate);

		instancingData[itrNum_].WVP = matWorld;
		instancingData[itrNum_].World = Matrix4x4::identity;
		instancingData[itrNum_].Color = (*itr).color;
		instancingData[itrNum_].uvTansform = (*itr).uvTransform.matWorld;
		itrNum_++;
	}


	// コマンドコール
	CommandCall(pParticle->GetUseTexture());
}



/// <summary>
/// コマンドコール処理
/// </summary>
void ParticlePlane::CommandCall(uint32_t texHandle) {

	// RootSignatureを設定。
	DirectXCommon::GetInstance()->GetCommandList()->SetGraphicsRootSignature(ParticleGraphicPipeline::GetInstance()->GetPsoProperty().rootSignature);
	// PSOを設定
	DirectXCommon::GetInstance()->GetCommandList()->SetPipelineState(ParticleGraphicPipeline::GetInstance()->GetPsoProperty().graphicsPipelineState);

	///// いざ描画！！！！！
	// VBVを設定
	DirectXCommon::GetInstance()->GetCommandList()->IASetVertexBuffers(0, 1, &resource_.VertexBufferView);
	DirectXCommon::GetInstance()->GetCommandList()->IASetIndexBuffer(&resource_.IndexBufferView);

	// 形状を設定
	DirectXCommon::GetInstance()->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// CBVを設定する
	DirectXCommon::GetInstance()->GetCommandList()->SetGraphicsRootConstantBufferView(0, resource_.Material->GetGPUVirtualAddress());

	// DescriptorTableを設定する
	DescriptorManager::SetGraphicsRootDescriptorTable(1, dsvIndex_);
	if (!texHandle == 0) {
		DescriptorManager::SetGraphicsRootDescriptorTable(2, texHandle);
	}

	// 描画！(DrawCall / ドローコール)。3頂点で1つのインスタンス。インスタンスについては今後
	DirectXCommon::GetInstance()->GetCommandList()->DrawIndexedInstanced(6, NumInstance_, 0, 0, 0);
}
