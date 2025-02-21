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

	// 初期化バインド
	Bind_Init(); 
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
	handles_.vertex.UpdateData(model_->GetMeshData().vertices.data());
	// IBV
	handles_.indeces.UpdateData(model_->GetMeshData().indices.data());
	// Transform
	handles_.transform.UpdateData(metaDataArray, instanceNum_);
	// Material
	handles_.material.UpdateData(materials, instanceNum_);
	

	// 描画バインド
	Bind_Draw();
}


/// <summary>
/// パーティクルの要素のバインド
/// </summary>
void GPUParticle::Bind_ParticleProp()
{
	handles_.particleElement.BindComputeSRV_Instanced(0);
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


	// Particleの要素の初期化値
	handles_.particleElement.BindComputeSRV_Instanced(0);

	// Dispach
	commands.List->Dispatch(1, 1, 1);
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
	// Transform
	handles_.transform.BindGraphicsSRV_Instanced(0);
	// ParticleElement
	handles_.particleElement.BindGraphicsSRV_Instanced(0);
	// Camera
	cameraManager_->CommandCall(1);
	// Material
	handles_.material.BindGraphicsSRV_Instanced(3);
	// MaterialTexture
	handles_.material.BindGraphicsSRV(2, model_->GetMaterialData().textureHandle);
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
	// transform
	handles_.transform.CreateCBV(instanceNum_);
	handles_.transform.CreateInstancingResource(instanceNum_); // インスタンス数分つくる
	// material
	handles_.material.CreateCBV(instanceNum_);
	handles_.material.CreateInstancingResource(instanceNum_);
	// light
	//buffers_.light.CreateCBV();
}

