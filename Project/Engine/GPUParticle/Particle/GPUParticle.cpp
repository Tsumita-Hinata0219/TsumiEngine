#include "GPUParticle.h"
#include "Camera/Manager/CameraManager.h"
#include "3D/Model/Manager/ModelManager.h"


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
	instanceNum_ = instanceNum * minInstanceNum_;

	// BufferResourceを作成
	CreateBufferResource();

	// 初期化バインド
	Bind_Init(); 
}


/// <summary>
/// 更新処理
/// </summary>
void GPUParticle::Update()
{
	// 更新バインド
	Bind_Update();
}


/// <summary>
/// 描画処理
/// </summary>
void GPUParticle::Draw()
{
	// ここで書き込み
	// VBV
	handles_.vertex.UpdateData(model_->GetMeshData().vertices.data());
	// IBV
	handles_.indeces.UpdateData(model_->GetMeshData().indices.data());
	
	// 描画バインド
	Bind_Draw();
}


/// <summary>
/// パーティクルの要素のバインド
/// </summary>
void GPUParticle::Bind_ParticleProp(UINT num)
{
	handles_.particleElement.BindComputeSRV_Instanced(num);
}


/// <summary>
/// フリーリストのバインド
/// </summary>
void GPUParticle::Bind_FreeList(UINT num)
{
	freeListBuffer_.BindComputeSRV_Instanced(num);
}


/// <summary>
/// フリーリストインデックスのバインド
/// </summary>
void GPUParticle::Bind_FreeListIndex(UINT num)
{
	freeListIndexBuffer_.BindComputeSRV_Instanced(num);
}


/// <summary>
/// UAVBarrierを設定
/// </summary>
void GPUParticle::SetUAVBarrier()
{
	// Commandの取得
	Commands commands = CommandManager::GetInstance()->GetCommands();
	// UAVBarrier
	D3D12_RESOURCE_BARRIER uavBarrier{};
	uavBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_UAV;
	uavBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	uavBarrier.UAV.pResource = handles_.particleElement.GetResource();
	commands.List->ResourceBarrier(1, &uavBarrier);
}


/// <summary>
/// バインド
/// </summary>
void GPUParticle::Bind_Init()
{
	// Commandの取得
	Commands commands = CommandManager::GetInstance()->GetCommands();

	// PipeLineCheck
	PipeLineManager::SetPipeLine(PipeLine::Container::Compute, PipeLine::Category::GPUParticle_Init);

	// Particleの初期化値
	handles_.particleElement.BindComputeSRV_Instanced(0);

	// FreeListの初期化
	freeListBuffer_.BindComputeSRV_Instanced(1);

	// FreeListIndexの初期化
	freeListIndexBuffer_.BindComputeSRV_Instanced(2);

	// Dispach
	commands.List->Dispatch(1, 1, 1);

	// Barrierを張る
	this->SetUAVBarrier();
}
void GPUParticle::Bind_Update()
{
	// Commandの取得
	Commands commands = CommandManager::GetInstance()->GetCommands();

	// PipeLineCheck
	PipeLineManager::SetPipeLine(PipeLine::Container::Compute, PipeLine::Category::GPUParticle_Update);

	// Particleの要素の初期化値
	handles_.particleElement.BindComputeSRV_Instanced(0);

	// Dispach
	commands.List->Dispatch(1, 1, 1);

	// Barrierを張る
	this->SetUAVBarrier();
}
void GPUParticle::Bind_Draw()
{
	// Commandの取得
	Commands commands = CommandManager::GetInstance()->GetCommands();

	// PipeLineCheck
	PipeLineManager::SetPipeLine(PipeLine::Container::Graphic, PipeLine::Category::GPUParticle_Draw);

	// VertexBufferView
	handles_.vertex.IASetVertexBuffers(1);

	// IndexBufferView
	handles_.indeces.IASetIndexBuffer();

	// ParticleElement : VS
	handles_.particleElement.BindGraphicsSRV_Instanced(0);

	// Camera
	cameraManager_->CommandCall(1);

	// ParticleElement : PS
	handles_.particleElement.BindGraphicsSRV_Instanced(2);

	// MaterialTexture
	handles_.material.BindGraphicsSRV(3, model_->GetMaterialData().textureHandle);

	// Draw!!
	commands.List->DrawInstanced(UINT(model_->GetMeshData().indices.size()), instanceNum_, 0, 0);
}


/// <summary>
/// BufferResourceの作成
/// </summary>
void GPUParticle::CreateBufferResource()
{
	// mesh
	handles_.mesh.CreateCBV(UINT(model_->GetMeshData().vertices.size()));
	// vertexBufferView
	handles_.vertex.CreateCBV(UINT(model_->GetMeshData().vertices.size()));
	handles_.vertex.CreateVertexBufferView();
	// indexBufferView
	handles_.indeces.CreateCBV(UINT(model_->GetMeshData().indices.size()));
	handles_.indeces.CreateIndexBufferView();
	// ParticleElement
	handles_.particleElement.CreateUAV(instanceNum_);
	// PreView
	handles_.preView.CreateCBV();
	// material
	handles_.material.CreateCBV(instanceNum_);
	handles_.material.CreateInstancingResource(instanceNum_);
	// FreeList
	freeListBuffer_.CreateUAV(instanceNum_);
	// FreeListIndex
	freeListIndexBuffer_.CreateUAV(instanceNum_);
}

