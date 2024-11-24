#include "GPUParticleEmitter.h"
#include "GameManager/GameManager.h"


/// <summary>
/// 初期化処理
/// </summary>
void Particle::Emit::GPUParticleEmitter::Init()
{
	// BufferResourceを作成
	CreateBufferResource();

	// SphereEmitterの初期値
	datas_.sphereEmitter.count = 10;
	datas_.sphereEmitter.frequency = 0.5f;
	datas_.sphereEmitter.frequencyTime = 0.0f;
	datas_.sphereEmitter.translate = Vector3::zero;
	datas_.sphereEmitter.radius = 1.0f;
	datas_.sphereEmitter.emit = 0;

	// PerFrameの初期値
	scope_ = { 0.0f, 1000.0f };
	datas_.perFrame.time = 0.0f;
	datas_.perFrame.deltaTime = g_ElapsedTime + RandomGenerator::getRandom(scope_);
}


/// <summary>
/// 更新処理
/// </summary>
void Particle::Emit::GPUParticleEmitter::Update()
{
	datas_.perFrame.deltaTime = g_ElapsedTime + RandomGenerator::getRandom(scope_);

	datas_.sphereEmitter.frequencyTime++;
	// 射出間隔を上回ったら射出許可をだして時間を調整
	if (datas_.sphereEmitter.frequency <= datas_.sphereEmitter.frequencyTime) {
		datas_.sphereEmitter.frequencyTime -= datas_.sphereEmitter.frequency;
		datas_.sphereEmitter.emit = 1;
	}
	else { // 射出間隔を上回っていないので、射出許可は出せない
		datas_.sphereEmitter.emit = 0;
	}
}


/// <summary>
/// 描画処理
/// </summary>
void Particle::Emit::GPUParticleEmitter::Draw()
{
}


/// <summary>
/// Particle発生処理
/// </summary>
void Particle::Emit::GPUParticleEmitter::Emit(std::unique_ptr<GPUParticle>& particle)
{
	// Commandの取得
	Commands commands = CommandManager::GetInstance()->GetCommands();

	// PipeLineCheck
	PipeLineManager::PipeLineCheckAndSet(PipeLineType::CSEmitter, false);

	// Emitter
	buffers_.sphereEmitter.Map();
	buffers_.sphereEmitter.WriteData(&datas_.sphereEmitter);
	buffers_.sphereEmitter.UnMap();
	// PerFrame
	buffers_.perFrame.Map();
	buffers_.perFrame.WriteData(&datas_.perFrame);
	buffers_.perFrame.UnMap();

	// Particleのコマンドコール
	particle->ComputeCommandCall();
	// Emitterのコマンドコール
	buffers_.sphereEmitter.ComputeCommandCall(2);
	// PerFrameのコマンドコール
	buffers_.perFrame.ComputeCommandCall(3);

	// Dispach 
	commands.List->Dispatch(1, 1, 1);
}


/// <summary>
/// BufferResourceの作成
/// </summary>
void Particle::Emit::GPUParticleEmitter::CreateBufferResource()
{
	// SphereEmitter
	buffers_.sphereEmitter.CreateCBV();
	// PerFrame
	buffers_.perFrame.CreateCBV();

}
