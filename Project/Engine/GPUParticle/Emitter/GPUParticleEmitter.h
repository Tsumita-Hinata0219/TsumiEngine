#pragma once

#include "../Structure/EmitterStructure.h"
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
	void Create(std::weak_ptr<GPUParticle> pParticle);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// Particleを沸かせる
	/// </summary>
	void Emit();

#pragma region Accessor

	// エミッターデータ
	const std::weak_ptr<T> GetEmitData() { return this->emitterData_; }
	void SetEmitData(const T& setData) { this->emitterData_ = setData; }

	// エミッターコンフィグ
	const std::weak_ptr<GpuEmitter::EmitterConfig> GetEmitConfig() { return this->emitConfigData_; }

#pragma endregion 


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


private:

	// パーティクルのPtr
	std::weak_ptr<GPUParticle> particlePtr_;

	// エミッターデータ
	std::shared_ptr<T> emitterData_;
	BufferResource<T> emitterBuffer_;

	// 射出に関する
	std::shared_ptr<GpuEmitter::EmitterConfig> emitConfigData_;
	BufferResource<GpuEmitter::EmitterConfig> emitConfigBuffer_;

	// GPUに使う乱数シード情報
	GpuEmitter::RandomSeed seedData_{};
	BufferResource<GpuEmitter::RandomSeed> seedBuffer_;

	// 前回リセットした時点の時間
	float lastResetTime_ = 0.0f;

	// 時間記録クラス
	TimeSystem* timeSys_ = nullptr;
};



/// <summary>
/// 生成
/// </summary>
template<typename T>
inline void GPUParticleEmitter<T>::Create(std::weak_ptr<GPUParticle> pParticle)
{
	// TimeSystem
	timeSys_ = TimeSystem::GetInstance();

	// パーティクルのptrを受け取る
	particlePtr_ = pParticle;

	// エミッター作成
	emitterData_ = std::make_shared<T>();
	// エミッターのバッファー作成
	emitterBuffer_.CreateCBV();

	// エミッターコンフィグ作成
	emitConfigData_ = std::make_shared<GpuEmitter::EmitterConfig>();
	// エミッターコンフィグのバッファー作成
	emitConfigBuffer_.CreateCBV();

	// シードデータの初期設定
	seedData_.gameTime = timeSys_->Get_SinceStart();
	seedData_.dynamicTime = RandomGenerator::getRandom(Scope(0.0f, 1000.0f));
	// シードデータのバッファー作成
	seedBuffer_.CreateCBV();
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
inline void GPUParticleEmitter<T>::Emit()
{
	// データの書き込み
	WriteData();

	// Commandの取得
	Commands commands = CommandManager::GetInstance()->GetCommands();

	// PipeLineCheck
	PipeLineManager::SetPipeLine(PipeLine::Container::Compute, PipeLine::Category::Particle_EmitterSphere);

	// Particle
	particlePtr_.lock()->Bind_ParticleProp(0);

	// FreeList
	particlePtr_.lock()->Bind_FreeList(1);

	// FreeListIndex
	particlePtr_.lock()->Bind_FreeListIndex(2);

	// Emitter
	emitterBuffer_.BindComputeCBV(3);

	// EmitterConfig
	emitConfigBuffer_.BindComputeCBV(4);

	// RandomSeed
	seedBuffer_.BindComputeCBV(5);

	// Dispach
	commands.List->Dispatch(1, 1, 1);

	// Barrierを張る
	particlePtr_.lock()->SetUAVBarrier();
}


/// <summary>
/// タイマー更新
/// </summary>
template<typename T>
inline void GPUParticleEmitter<T>::TimeUpdate()
{
	emitConfigData_->elapsedTime += 1.0f / 60.0f; // δタイムを加算
	// 射出間隔を上回ったら射出許可を出して時間を調整
	if (emitConfigData_->spawnInterval <= emitConfigData_->elapsedTime)
	{
		emitConfigData_->elapsedTime -= emitConfigData_->elapsedTime;
		emitConfigData_->isEmitting = 1;
	}
	else {
		emitConfigData_->isEmitting = 0;
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
	emitterBuffer_.UpdateData(emitterData_.get());

	// EmitterConfig
	emitConfigBuffer_.UpdateData(emitConfigData_.get());

	// SeedData
	seedBuffer_.UpdateData(&seedData_);
}

