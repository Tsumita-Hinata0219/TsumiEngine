#include "GPUParticle.h"
#include "3D/Model/Manager/ModelManager.h"


/// <summary>
/// 初期化処理
/// </summary>
void GPUParticle::Init(uint32_t instanceNum)
{
	ModelManager* modelManager = ModelManager::GetInstance();
	modelManager->LoadModel("Obj/Plane", "Plane.obj");
	//model_ = modelManager->GetModel("Plane");

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
	buffers_.vertex.Map();
	//buffers_.vertex.WriteData(model_->GetMeshData().vertices.data());
	buffers_.vertex.UnMap();
	// IBV
	buffers_.indeces.Map();
	//buffers_.indeces.WriteData(model_->GetMeshData().indices.data());
	buffers_.indeces.UnMap();
	// Transform
	buffers_.transform.Map();
	buffers_.transform.WriteData(metaDataArray, instanceNum_);
	buffers_.transform.UnMap();
	// Material
	buffers_.material.Map();
	buffers_.material.WriteData(materials, instanceNum_);
	buffers_.material.UnMap();
	

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
	PipeLineManager::PipeLineCheckAndSet(PipeLineType::GPUParticle_Init, false);

	// Particleの要素の初期化値
	buffers_.particleElement.ComputeCommandCallInstancingSRV(0);

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
	PipeLineManager::PipeLineCheckAndSet(PipeLineType::GPUParticle_Draw);

	// VertexBufferView
	buffers_.vertex.IASetVertexBuffers(1);
	// IndexBufferView
	buffers_.indeces.IASetIndexBuffer();
	// Transform
	//buffers_.transform.GraphicsCommandCallInstancingSRV(0);
	// ParticleElement
	buffers_.particleElement.GraphicsCommandCallInstancingSRV(0);
	// Camera
	cameraManager_->CommandCall(1);
	// Material
	//buffers_.material.GraphicsCommandCallInstancingSRV(3);
	// MaterialTexture
	//buffers_.material.GraphicsCommandCallSRV(2, model_->GetMaterialData().textureHandle);
	// Light
	//buffers_.light.CommandCall(4);
	// Draw!!
	//commands.List->DrawInstanced(UINT(model_->GetMeshData().indices.size()), instanceNum_, 0, 0);
}


/// <summary>
/// BufferResourceの作成
/// </summary>
void GPUParticle::CreateBufferResource()
{
	// mesh
	//buffers_.mesh.CreateResource(UINT(model_->GetMeshData().vertices.size()));
	// vertexBufferView
	//buffers_.vertex.CreateResource(UINT(model_->GetMeshData().vertices.size()));
	buffers_.vertex.CreateVertexBufferView();
	// indexBufferView
	//buffers_.indeces.CreateResource(UINT(model_->GetMeshData().indices.size()));
	buffers_.indeces.CreateIndexBufferView();
	// ParticleElement
	buffers_.particleElement.CreateUAV(instanceNum_);
	// PreView
	buffers_.preView.CreateCBV();
	// transform
	buffers_.transform.CreateResource(instanceNum_);
	buffers_.transform.CreateInstancingResource(instanceNum_); // インスタンス数分つくる
	// material
	buffers_.material.CreateResource(instanceNum_);
	buffers_.material.CreateInstancingResource(instanceNum_);
	// light
	//buffers_.light.CreateResource();
}

