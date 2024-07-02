#include "Skybox.h"



// 初期化処理
void Skybox::Initialize()
{
	// テクスチャの読み込み
	this->texture_ = TextureManager::LoadTexture("Texture", "airport_4k.dds");

	// リソースの作成
	resource_.Vertex = CreateResource::CreateBufferResource(sizeof(VertexData) * 8);
	resource_.Material = CreateResource::CreateBufferResource(sizeof(Material));
	resource_.VertexBufferView = CreateResource::CreateVertexBufferView(sizeof(VertexData) * 8, resource_.Vertex.Get(), 8);
}


// 更新処理
void Skybox::Update()
{


}


// 描画処理
void Skybox::Draw(Camera* camera)
{
	camera;
}


// コマンドコール
void Skybox::CommandCall(Camera* camera)
{
	camera;

}
