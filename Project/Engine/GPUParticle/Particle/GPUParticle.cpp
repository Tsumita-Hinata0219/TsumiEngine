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
}


/// <summary>
/// BufferResourceの作成
/// </summary>
void GPUParticle::CreateBufferResource()
{
}

