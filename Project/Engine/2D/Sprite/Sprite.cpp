#include "Sprite.h"
#include "Camera/Manager/CameraManager.h"



// 初期化処理
void Sprite::Init(Vector2 size)
{
	// CameraManagerのインスタンスの取得
	cameraManager_ = CameraManager::GetInstance();

	// サイズの初期設定
	size_ = size;

	// 基準の初期設定。左上
	anchor_ = SpriteAnchor::TopLeft;

	// TextureはデフォではuvChecker
	datas_.material.textureHandle = 
		TextureManager::LoadTexture("Texture", "uvChecker.png");

	// Mask画像はデフォではuvChecker
	datas_.dissolve.maskTexHandle = 
		TextureManager::LoadTexture("Texture", "uvChecker.png");

	// DatasをもとにBufferを作成
	CreateBufferResource();
}


// 描画処理
void Sprite::Draw(Transform& transform)
{
	// cameraResourceの取得
	auto cameraResource = cameraManager_->GetResource();

	// --- 諸々の計算 ---
	transform.UpdateMatrix();
	transform.transformationMatData.World = transform.matWorld;
	transform.transformationMatData.WVP =
		transform.transformationMatData.World * cameraResource->viewMatrix * cameraResource->projectionMatrix;
	transform.transformationMatData.WorldInverseTranspose = Transpose(Inverse(transform.matWorld));

	// --- Meshの設定 --- 
	SetMeshData();

	// --- ここで書き込み ---
	// VBV
	buffers_.vertex.Map();
	buffers_.vertex.WriteData(datas_.mesh.vertices.data());
	buffers_.vertex.UnMap();
	// IBV
	buffers_.indeces.Map();
	buffers_.indeces.WriteData(datas_.mesh.indices.data());
	buffers_.indeces.UnMap();
	// Material
	buffers_.material.Map();
	buffers_.material.WriteData(&datas_.material);
	buffers_.material.UnMap();
	// Dissolve
	buffers_.dissolve.Map();
	buffers_.dissolve.WriteData(&datas_.dissolve);
	buffers_.dissolve.UnMap();
	// Transform
	buffers_.transform.Map();
	buffers_.transform.WriteData(&transform.transformationMatData);
	buffers_.transform.UnMap();

	// コマンドコール
	CommandCall();
}


// コマンドコール
void Sprite::CommandCall()
{
	// Commandの取得
	Commands commands = CommandManager::GetInstance()->GetCommands();

	// PipeLineCheck
	PipeLineManager::SetPipeLine(PipeLine::Container::Graphic, PipeLine::Category::Object2D);

	// VertexBufferView
	buffers_.vertex.IASetVertexBuffers(1);
	// IndexBufferView
	buffers_.indeces.IASetIndexBuffer();
	// Material
	buffers_.material.GraphicsCommandCall(0);
	// Dissolve
	buffers_.dissolve.GraphicsCommandCall(4);
	// Transform
	buffers_.transform.GraphicsCommandCall(1);
	// View
	CameraManager::GetInstance()->CommandCall(2);
	// MaterialTexture
	//SRVManager::SetGraphicsRootDescriptorTable(3, datas_.material.textureHandle);
	buffers_.material.GraphicsCommandCallSRV(3, datas_.material.textureHandle);
	// MaskTexture
	//SRVManager::SetGraphicsRootDescriptorTable(5, datas_.dissolve.maskTexHandle);
	buffers_.material.GraphicsCommandCallSRV(5, datas_.dissolve.maskTexHandle);
	// Draw!!
	commands.List->DrawIndexedInstanced(6, 1, 0, 0, 0);
}


// DatasをもとにBufferを作成
void Sprite::CreateBufferResource()
{
	// VerticesとIndicesのresize
	datas_.mesh.vertices.resize(verticesSize_);
	datas_.mesh.indices.resize(indicesSize_);

	// mesh
	buffers_.mesh.CreateResource(UINT(datas_.mesh.vertices.size()));
	// vertexBufferView
	buffers_.vertex.CreateResource(UINT(datas_.mesh.vertices.size()));
	buffers_.vertex.CreateVertexBufferView();
	// indexBufferView
	buffers_.indeces.CreateResource(UINT(datas_.mesh.indices.size()));
	buffers_.indeces.CreateIndexBufferView();
	// material
	buffers_.material.CreateResource();
	// Dissolve
	buffers_.dissolve.CreateResource();
	// transform
	buffers_.transform.CreateResource();
}


// 四角形の頂点の設定
void Sprite::SetMeshData()
{
	// Anchorで処理を変える
	SP::MeshData mesh{};
	// VerticesとIndicesのresize
	mesh.vertices.resize(verticesSize_);
	mesh.indices.resize(indicesSize_);

	// --- Vertices ---
	switch (anchor_)
	{
	case SpriteAnchor::TopLeft:
		// 左下
		mesh.vertices[0].position = { 0.0f, size_.y, 0.0f, 1.0f };
		// 左上
		mesh.vertices[1].position = { 0.0f, 0.0f, 0.0f, 1.0f };
		// 右下
		mesh.vertices[2].position = { size_.x, size_.y, 0.0f, 1.0f };
		// 右上
		mesh.vertices[3].position = { size_.x, 0.0f, 0.0f, 1.0f };
		break;

	case SpriteAnchor::Center:
		// 左下
		mesh.vertices[0].position = { -size_.x / 2.0f, size_.y / 2.0f, 0.0f, 1.0f };
		// 左上
		mesh.vertices[1].position = { -size_.x / 2.0f, -size_.y / 2.0f, 0.0f, 1.0f };
		// 右下
		mesh.vertices[2].position = { size_.x / 2.0f, size_.y / 2.0f, 0.0f, 1.0f };
		// 右上
		mesh.vertices[3].position = { size_.x / 2.0f, -size_.y / 2.0f, 0.0f, 1.0f };
		break;
	}
	// 左下
	mesh.vertices[0].texCoord = src_.LeftDown;
	// 左上
	mesh.vertices[1].texCoord = src_.LeftUp;
	// 右下
	mesh.vertices[2].texCoord = src_.RightDown;
	// 右上
	mesh.vertices[3].texCoord = src_.RightUp;

	// --- Indices ---
	mesh.indices[0] = 0; mesh.indices[1] = 1; mesh.indices[2] = 2;
	mesh.indices[3] = 1; mesh.indices[4] = 3; mesh.indices[5] = 2;

	// DatasのMeshに値をいれる
	datas_.mesh = mesh;
}
