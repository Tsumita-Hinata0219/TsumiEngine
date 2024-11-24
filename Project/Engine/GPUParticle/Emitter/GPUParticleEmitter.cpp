#include "GPUParticleEmitter.h"


/// <summary>
/// 初期化処理
/// </summary>
void Particle::Emit::GPUParticleEmitter::Init()
{
	// BufferResourceを作成
	emitBuffer_.CreateCBV();

	// Dataの初期値
	emitData_.count = 10;
	emitData_.frequency = 0.5f;
	emitData_.frequencyTime = 0.0f;
	emitData_.translate = Vector3::zero;
	emitData_.radius = 1.0f;
	emitData_.emit = 0;
}


/// <summary>
/// 更新処理
/// </summary>
void Particle::Emit::GPUParticleEmitter::Update()
{
	emitData_.frequencyTime++;
	// 射出間隔を上回ったら射出許可をだして時間を調整
	if (emitData_.frequency <= emitData_.frequencyTime) {
		emitData_.frequencyTime -= emitData_.frequency;
		emitData_.emit = 1;
	}
	else { // 射出間隔を上回っていないので、射出許可は出せない
		emitData_.emit = 0;
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
	emitBuffer_.Map();
	emitBuffer_.WriteData(&emitData_);
	emitBuffer_.UnMap();

	// Emitterのコマンドコール
	emitBuffer_.ComputeCommandCall(0);
	// Particleのコマンドコール
	particle->ComputeCommandCall(1);

	// Dispach 
	commands.List->Dispatch(1, 1, 1);
}
