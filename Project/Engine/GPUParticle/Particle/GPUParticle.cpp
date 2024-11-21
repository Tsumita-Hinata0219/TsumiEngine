#include "GPUParticle.h"
#include "3D/Model/ModelManager/ModelManager.h"


/// <summary>
/// 初期化処理
/// </summary>
void GPUParticle::Init(uint32_t instanceNum)
{
	ModelManager* modelManager = ModelManager::GetInstance();
	modelManager->LoadModel("Obj/Plane", "Plane.obj");
	model_ = modelManager->GetModel("Plane");

	// CameraManagerのインスタンス取得
	cameraManager_ = CameraManager::GetInstance();

	// インスタンス数の設定
	instanceNum_ = instanceNum;

	// BufferResourceを作成
	CreateBufferResource();

	// 初期化コマンドコール <-多分必要になる
	CommandCallInit(); 
}


/// <summary>
/// 更新処理
/// </summary>
void GPUParticle::Update()
{



	// 更新コマンドコール <-多分必要になる
	CommandCallUpdate();
}


/// <summary>
/// 描画処理
/// </summary>
void GPUParticle::Draw()
{
	// ここで書き込み
	// VBV
	buffers_.vertex.Map();
	buffers_.vertex.WriteData(model_->GetMeshData().vertices.data());
	buffers_.vertex.UnMap();
	// IBV
	buffers_.indeces.Map();
	buffers_.indeces.WriteData(model_->GetMeshData().indices.data());
	buffers_.indeces.UnMap();


	// 描画コマンドコール
	CommandCallDraw();
}


/// <summary>
/// コマンドコール
/// </summary>
void GPUParticle::CommandCallInit()
{

}
void GPUParticle::CommandCallUpdate()
{

}
void GPUParticle::CommandCallDraw()
{
	// Commandの取得
	Commands commands = CommandManager::GetInstance()->GetCommands();

	// PipeLineCheck
	PipeLineManager::PipeLineCheckAndSet(PipeLineType::Object3D);

	// VertexBufferView
	buffers_.vertex.IASetVertexBuffers(1);
	// IndexBufferView
	buffers_.indeces.IASetIndexBuffer();
	// Transform
	buffers_.transform.CommandCall(0);
	// Camera
	cameraManager_->CommandCall(1);
	// Material
	buffers_.material.CommandCall(3);
	// MaterialTexture
	buffers_.material.CommandCallSRV(2, datas_.material.textureHandle);
	// Light
	//buffers_.light.CommandCall(4);
	// Draw!!
	commands.List->DrawInstanced(UINT(model_->GetMeshData().indices.size()), instanceNum_, 0, 0);
}


/// <summary>
/// BufferResourceの作成
/// </summary>
void GPUParticle::CreateBufferResource()
{
	// mesh
	buffers_.mesh.CreateResource(UINT(model_->GetMeshData().vertices.size()));
	// vertexBufferView
	buffers_.vertex.CreateResource(UINT(model_->GetMeshData().vertices.size()));
	buffers_.vertex.CreateVertexBufferView();
	// indexBufferView
	buffers_.indeces.CreateResource(UINT(model_->GetMeshData().vertices.size()));
	buffers_.indeces.CreateIndexBufferView();
	// transform
	buffers_.transform.CreateResource(instanceNum_);
	buffers_.transform.CreateInstancingResource(instanceNum_); // インスタンス数分つくる
	// material
	buffers_.material.CreateResource(instanceNum_);
	buffers_.material.CreateInstancingResource(instanceNum_);
	// light
	//buffers_.light.CreateResource();
}

