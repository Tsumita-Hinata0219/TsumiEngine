#pragma once

#include "../Structure/ParticleStructure.h"
#include "../Resources/ParticleResources.h"
#include "../Particle/GPUParticle.h"

#include  "Utilities/RandomGenerator/RandomGenerator.h"
#include "Utilities/TimeSystem/TimeSystem.h"


/* GPUParticleのエミッター */
template <typename T>
class GPUParticleEmitter {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GPUParticleEmitter() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GPUParticleEmitter() = default;

	/// <summary>
	/// 生成
	/// </summary>
	void Create(std::unique_ptr<GPUParticle>& particle);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// Particleを沸かせる
	/// </summary>
	void Emit(std::unique_ptr<GPUParticle>& particle);


private:

	/// <summary>
	/// タイマー更新
	/// </summary>
	void TimeUpdate();

	/// <summary>
	/// シードの更新
	/// </summary>
	void UpdateSeedData();

	/// <summary>
	/// Bufferへデータの書き込み
	/// </summary>
	void WriteData();

#pragma region Accessor

	// エミッターデータの設定
	void SetEmitData(const T& setData) { this->emitterData_ = setData; }

#pragma endregion 


private:

	// 書き込み用のバッファー
	BufferResource<T> emitterBuffer_;

	// エミッターデータ
	T emitterData_;

	// 射出に関する
	GpuParticle::EmitterConfig emitConfig_{};

	// GPUに使う乱数シード情報
	GpuParticle::RandomSeed seedData_{};
	BufferResource<GpuParticle::RandomSeed> seedBuffer_;

	// 前回リセットした時点の時間
	float lastResetTime_ = 0.0f;

	// 時間記録クラス
	TimeSystem* timeSys_ = nullptr;
};



/// <summary>
/// 生成
/// </summary>
template<typename T>
inline void GPUParticleEmitter<T>::Create(std::unique_ptr<GPUParticle>& particle)
{
	particle;

	// TimeSystem
	timeSys_ = TimeSystem::GetInstance();

	// SeedData
	seedData_.gameTime = timeSys_->Get_SinceStart();
	seedData_.dynamicTime = RandomGenerator::getRandom(Scope(0.0f, 1000.0f));
	// Seedのバッファー作成
	seedBuffer_.CreateCBV();

	// Emitterのバッファー作成
	emitterBuffer_.CreateCBV();
}


/// <summary>
/// 更新処理
/// </summary>
template<typename T>
inline void GPUParticleEmitter<T>::Update()
{
	// タイマー更新
	TimeUpdate();

	// シードデータの更新
	UpdateSeedData();

	// データの書き込み
	WriteData();
}


/// <summary>
/// Particleを沸かせる
/// </summary>
template<typename T>
inline void GPUParticleEmitter<T>::Emit(std::unique_ptr<GPUParticle>& particle)
{
	// Commandの取得
	Commands commands = CommandManager::GetInstance()->GetCommands();

	// PipeLineCheck
	PipeLineManager::SetPipeLine(PipeLine::Container::Compute, PipeLine::Category::Particle_EmitterSphere);

	// Particle
	particle->Bind_ParticleProp();

	// Emmiter
	emitterBuffer_.BindComputeCBV(1);

	// RandomSeed
	seedBuffer_.BindComputeCBV(2);

	// Dispach
	commands.List->Dispatch(1, 1, 1);
}


/// <summary>
/// タイマー更新
/// </summary>
template<typename T>
inline void GPUParticleEmitter<T>::TimeUpdate()
{
	emitConfig_.intervalTime += 1.0f / 60.0f; // δタイムを加算
	// 射出間隔を上回ったら射出許可を出して時間を調整
	if (emitConfig_.emitInterval <= emitConfig_.intervalTime) 
	{
		emitConfig_.intervalTime -= emitConfig_.intervalTime;
		emitConfig_.enableEmit = 1;
		// 射出間隔を上回っていないので、射出許可は出せない
	}
	else {
		emitConfig_.enableEmit = 0;
	}
}


/// <summary>
/// シードの更新
/// </summary>
template<typename T>
inline void GPUParticleEmitter<T>::UpdateSeedData()
{
	// ゲーム開始からの時間を取得
	seedData_.gameTime = timeSys_->Get_SinceStart();
	// 初期乱数値 + 開始からの時間
	seedData_.dynamicTime += seedData_.gameTime;

	// 600秒（10分）ごとにリセット
	if (seedData_.gameTime - lastResetTime_ >= 600.0f) {
		seedData_.dynamicTime = RandomGenerator::getRandom(Scope(0.0f, 1000.0f));
		lastResetTime_ = seedData_.gameTime;
	}
}


/// <summary>
/// Bufferへデータの書き込み
/// </summary>
template<typename T>
inline void GPUParticleEmitter<T>::WriteData()
{
	// Emitter
	emitterBuffer_.UpdateData(&emitterData_);

	// SeedData
	seedBuffer_.UpdateData(&seedData_);
}

