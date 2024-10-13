#include "Sprite.h"
#include "GameObject/Camera/Manager/CameraManager.h"


/// <summary>
/// 初期化処理
/// </summary>
void Sprite::Init(Vector2 size, Vector4 color) {

	// 座標の設定
	worldTransform_.srt.translate = Vector3::zero;

	// サイズの設定
	size_ = size;

	// 色の設定
	color_ = color;

	// uvTransformの設定
	uvTransform_ = {
		{ 1.0f, 1.0f, 1.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
	};

	// テクスチャの設定
	// デフォルトではuvCheckerを使う
	useTexture_ = 1;

	// 
	anchor_ = SpriteAnchor::TopLeft;

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
void Sprite::Draw(uint32_t texHandle, WorldTransform& transform) {

	// 頂点データを設定する
	SetVertex(transform);

	// コマンドの取得
	Commands commands = CommandManager::GetInstance()->GetCommands();

	// PipeLineCheck
	PipeLineManager::PipeLineCheckAndSet(PipeLineType::Sprite);

	// 頂点の設定
	commands.List->IASetVertexBuffers(0, 1, &resource_.VertexBufferView); // VBVを設定
	commands.List->IASetIndexBuffer(&resource_.IndexBufferView);

	// Material用のCBufferの場所を設定
	commands.List->SetGraphicsRootConstantBufferView(0, resource_.Material->GetGPUVirtualAddress());

	// wvp用のCBufferの場所を設定
	commands.List->SetGraphicsRootConstantBufferView(1, transform.constBuffer->GetGPUVirtualAddress());

	// View用のCBufferの場所を設定
	CameraManager::GetInstance()->CommandCall(2);

	// DescriptorTableを設定する
	if (!texHandle == 0) {
		SRVManager::SetGraphicsRootDescriptorTable(3, texHandle);
	}

	// 描画！(DrawCall/ドローコール)
	commands.List->DrawIndexedInstanced(6, 1, 0, 0, 0);
}


/// <summary>
/// 頂点データを設定する
/// </summary>
void Sprite::SetVertex(WorldTransform transform) {

	VertexData* vertexData = nullptr;
	MaterialSprite* materialData = nullptr;
	uint32_t* indexData = nullptr;

	// 書き込みができるようにする
	resource_.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	resource_.Material->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	resource_.Index->Map(0, nullptr, reinterpret_cast<void**>(&indexData));

	// ワールドトランスフォームの設定
	worldTransform_ = transform;


	switch (anchor_) 
	{
	case SpriteAnchor::TopLeft:

		// 左下
		vertexData[0].position = { 0.0f, size_.y, 0.0f, 1.0f };

		// 左上
		vertexData[1].position = { 0.0f, 0.0f, 0.0f, 1.0f };

		// 右下
		vertexData[2].position = { size_.x, size_.y, 0.0f, 1.0f };

		// 右上
		vertexData[3].position = { size_.x, 0.0f, 0.0f, 1.0f };
		break;

	case SpriteAnchor::Center:

		// 左下
		vertexData[0].position = { -size_.x / 2.0f, size_.y / 2.0f, 0.0f, 1.0f };

		// 左上
		vertexData[1].position = { -size_.x / 2.0f, -size_.y / 2.0f, 0.0f, 1.0f };

		// 右下
		vertexData[2].position = { size_.x / 2.0f, size_.y / 2.0f, 0.0f, 1.0f };

		// 右上
		vertexData[3].position = { size_.x / 2.0f, -size_.y / 2.0f, 0.0f, 1.0f };
		break;
	}


	// 左下
	vertexData[0].texCoord = src_.LeftDown;

	// 左上
	vertexData[1].texCoord = src_.LeftUp;


	// 右下
	vertexData[2].texCoord = src_.RightDown;

	// 右上
	vertexData[3].texCoord = src_.RightUp;


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





// 初期化処理
void Sprite::Initn(Vector2 size)
{
	// CameraManagerのインスタンスの取得
	cameraManager_ = CameraManager::GetInstance();

	// サイズの初期設定
	size_ = size;

	// 基準の初期設定。左上
	anchor_ = SpriteAnchor::TopLeft;

	// vuTransformの初期化
	uvTransform_ = {
		Vector3::one,
		Vector3::zero,
		Vector3::zero,
	};

	// Mask画像はuvCheckerを入れておく
	datas_.dissolve.maskTexHandle = 
		TextureManager::LoadTexture("Texture", "uvChecker.png");

	// DatasをもとにBufferを作成
	CreateBufferResource();
}


// 描画処理
void Sprite::Draw(uint32_t texHandle, Transform& transform)
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

	// --- Materialの設定 ---
	datas_.material.textureHandle = texHandle;
	// uvTransformの設定
	datas_.material.uvTransform = 
		MakeAffineMatrix(uvTransform_.scale, uvTransform_.rotate, uvTransform_.translate);

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
	PipeLineManager::PipeLineCheckAndSet(PipeLineType::Object2D);

	// VertexBufferView
	buffers_.vertex.IASetVertexBuffers(1);
	// IndexBufferView
	buffers_.indeces.IASetIndexBuffer();
	// Material
	buffers_.material.CommandCall(0);
	// Dissolve
	buffers_.dissolve.CommandCall(1);
	// Transform
	buffers_.transform.CommandCall(1);
	// View
	CameraManager::GetInstance()->CommandCall(2);
	// MaterialTexture
	SRVManager::SetGraphicsRootDescriptorTable(3, datas_.material.textureHandle);
	// MaskTexture
	SRVManager::SetGraphicsRootDescriptorTable(5, datas_.dissolve.maskTexHandle);
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
