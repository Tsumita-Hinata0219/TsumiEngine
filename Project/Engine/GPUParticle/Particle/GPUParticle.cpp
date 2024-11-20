#include "GPUParticle.h"



/// <summary>
/// 初期化処理
/// </summary>
void GPUParticle::Init(uint32_t instanceNum)
{
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
	// Material
	buffers_.material.CommandCall(0);
	// Transform
	buffers_.transform.CommandCall(1);
	// Camera
	cameraManager_->CommandCall(2);
	// MaterialTexture
	//SRVManager::SetGraphicsRootDescriptorTable(3, datas_.material.textureHandle);
	buffers_.material.CommandCallSRV(3, datas_.material.textureHandle);
	// Light
	//buffers_.light.CommandCall(4);
	// Draw!!
	commands.List->DrawInstanced(6, instanceNum_, 0, 0);
}


/// <summary>
/// BufferResourceの作成
/// </summary>
void GPUParticle::CreateBufferResource()
{
	// mesh
	buffers_.mesh.CreateResource();
	// vertexBufferView
	buffers_.vertex.CreateResource();
	buffers_.vertex.CreateVertexBufferView();
	// indexBufferView
	buffers_.indeces.CreateResource();
	buffers_.indeces.CreateIndexBufferView();
	// material
	buffers_.material.CreateResource();
	// transform
	buffers_.transform.CreateResource(instanceNum_); // インスタンス数分つくる
	// light
	//buffers_.light.CreateResource();
}

