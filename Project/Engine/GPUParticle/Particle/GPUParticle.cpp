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
	instanceNum_ = instanceNum;

	// BufferResourceを作成
	CreateBufferResource();

	// 初期化コマンドコール <-多分必要になる
	CommandCall_Init(); 
}


/// <summary>
/// 更新処理
/// </summary>
void GPUParticle::Update()
{



	// 更新コマンドコール <-多分必要になる
	CommandCall_Update();
}


/// <summary>
/// 描画処理
/// </summary>
void GPUParticle::Draw(std::vector<Transform>& transforms, const std::vector<MaterialDataN>& materials)
{
	// 計算と抽出
	std::vector<TransformationMat> metaDataArray;
	for (auto& element : transforms) {
		element.UpdateMatrix();
		element.transformationMatData.World = element.matWorld;
		metaDataArray.push_back(element.transformationMatData);
	}


	// ここで書き込み
	// VBV
	handles_.vertex.Map();
	handles_.vertex.WriteData(model_->GetMeshData().vertices.data());
	handles_.vertex.UnMap();
	// IBV
	handles_.indeces.Map();
	handles_.indeces.WriteData(model_->GetMeshData().indices.data());
	handles_.indeces.UnMap();
	// Transform
	handles_.transform.Map();
	handles_.transform.WriteData(metaDataArray, instanceNum_);
	handles_.transform.UnMap();
	// Material
	handles_.material.Map();
	handles_.material.WriteData(materials, instanceNum_);
	handles_.material.UnMap();
	

	// 描画コマンドコール
	CommandCall_Draw();
}


/// <summary>
/// コマンドコール
/// </summary>
void GPUParticle::CommandCall_Init()
{
	// Commandの取得
	Commands commands = CommandManager::GetInstance()->GetCommands();

	// PipeLineCheck
	PipeLineManager::SetPipeLine(PipeLine::Container::Compute, PipeLine::Category::GPUParticle_Init);


	// Particleの要素の初期化値
	handles_.particleElement.ComputeCommandCallInstancingSRV(0);

	// Dispach
	commands.List->Dispatch(1, 1, 1);
}
void GPUParticle::CommandCall_Update()
{

}
void GPUParticle::CommandCall_Draw()
{
	// Commandの取得
	Commands commands = CommandManager::GetInstance()->GetCommands();

	// PipeLineCheck
	PipeLineManager::SetPipeLine(PipeLine::Container::Graphic, PipeLine::Category::GPUParticle_Draw);

	// VertexBufferView
	handles_.vertex.IASetVertexBuffers(1);
	// IndexBufferView
	handles_.indeces.IASetIndexBuffer();
	// Transform
	handles_.transform.GraphicsCommandCallInstancingSRV(0);
	// ParticleElement
	handles_.particleElement.GraphicsCommandCallInstancingSRV(0);
	// Camera
	cameraManager_->CommandCall(1);
	// Material
	handles_.material.GraphicsCommandCallInstancingSRV(3);
	// MaterialTexture
	handles_.material.GraphicsCommandCallSRV(2, model_->GetMaterialData().textureHandle);
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
	handles_.mesh.CreateResource(UINT(model_->GetMeshData().vertices.size()));
	// vertexBufferView
	handles_.vertex.CreateResource(UINT(model_->GetMeshData().vertices.size()));
	handles_.vertex.CreateVertexBufferView();
	// indexBufferView
	handles_.indeces.CreateResource(UINT(model_->GetMeshData().indices.size()));
	handles_.indeces.CreateIndexBufferView();
	// ParticleElement
	handles_.particleElement.CreateUAV(instanceNum_);
	// PreView
	handles_.preView.CreateCBV();
	// transform
	handles_.transform.CreateResource(instanceNum_);
	handles_.transform.CreateInstancingResource(instanceNum_); // インスタンス数分つくる
	// material
	handles_.material.CreateResource(instanceNum_);
	handles_.material.CreateInstancingResource(instanceNum_);
	// light
	//buffers_.light.CreateResource();
}

