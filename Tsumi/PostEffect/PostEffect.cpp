#include "PostEffect.h"



// 初期化処理
void PostEffect::Initialize()
{





	// リソースの作成
	resource_.Vertex = CreateResource::CreateBufferResource(sizeof(VertexData) * 4);
	resource_.Material = CreateResource::CreateBufferResource(sizeof(MaterialSprite));
	resource_.VertexBufferView = CreateResource::CreateVertexBufferView(sizeof(VertexData) * 4, resource_.Vertex.Get(), 4);

	resource_.Index = CreateResource::CreateBufferResource(sizeof(uint32_t) * 6);
	resource_.IndexBufferView = CreateResource::CreateIndexBufferview(sizeof(uint32_t) * 6, resource_.Index.Get());

	srv_ = DescriptorManager::CreateRenderTextureSRV()
}


// 描画処理
void PostEffect::Draw()
{







}


// 頂点データの設定
void PostEffect::SetVertex()
{





}


// コマンドコール
void PostEffect::CommandCall()
{



}
