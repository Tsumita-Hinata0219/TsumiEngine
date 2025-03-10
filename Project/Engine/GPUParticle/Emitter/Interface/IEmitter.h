#pragma once

#include "BufferResource/BufferResource.h"
#include "../../Structure/EmitterStructure.h"
#include "../../Structure/ParticleStructure.h"
#include "../../Structure/FieldStructure.h"
#include "../../Particle/GPUParticle.h"

#include  "Utilities/RandomGenerator/RandomGenerator.h"
#include "Utilities/TimeSystem/TimeSystem.h"


/* Emitterの基底クラス */
template <typename T>
class IEmitter {

public:

	/// <summary>
	/// コンストラク
	/// </summary>
	IEmitter() = default;

	/// <summary>
	/// デストラク
	/// </summary>
	~IEmitter() = default;

	/// <summary>
	/// 生成
	/// </summary>
	void Create();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw3D();

	/// <summary>
	/// 発生
	/// </summary>
	void Emit();


#pragma region Accessor

	// Emitter
	const std::weak_ptr<T> GetWeak_EmitData() { return this->emitData_; }

	// Emitter Range
	const std::weak_ptr<Emitter::EmitRange> GetWeak_RangeData() { return this->rangeData_; }

	// Emitter Config
	const std::weak_ptr<Emitter::EmitConfig> GetWeak_ConfigData() { return this->configData_; }

#pragma endregion 


private:

	/// <summary>
	/// Data生成
	/// </summary>
	void CreateData();

	/// <summary>
	/// Buffer生成
	/// </summary>
	void CreateBuffer();

	/// <summary>
	/// 射出データの更新
	/// </summary>
	void Update_ConfigData();

	/// <summary>
	/// 乱数シードデータの更新
	/// </summary>
	void Update_RandomSeedData();

	/// <summary>
	/// Bufferへデータ書き込み
	/// </summary>
	void WriteData();


protected:

	// PipeLineの種類
	PipeLine::Category pipeLine_Category = PipeLine::Category::None;
	PipeLine::SubFilter pipeLine_SubFileter = PipeLine::SubFilter::None;


private:
	
	// パーティクル
	std::unique_ptr<GPUParticle> particle_;

	// エミッター
	std::shared_ptr<T> emitData_;
	BufferResource<T> emitBuff_;

	// 範囲
	std::shared_ptr<Emitter::EmitRange> rangeData_;
	BufferResource<Emitter::EmitRange> rangeBuff_;

	// 射出
	std::shared_ptr<Emitter::EmitConfig> configData_;
	BufferResource<Emitter::EmitConfig> configBuff_;

	// 乱数シード
	std::shared_ptr<Emitter::RandomSeed> randSeedData_;
	BufferResource<Emitter::RandomSeed> randSeedBuff_;

	// 前回リセットした時点の時間
	float lastResetTime_ = 0.0f;
	// 時間記録クラス
	TimeSystem* timeSys_ = nullptr;
};



/// <summary>
/// 生成
/// </summary>
template<typename T>
inline void IEmitter<T>::Create()
{
	// TimeSystem
	timeSys_ = TimeSystem::GetInstance();

	// Data作成
	CreateData();

	// Buffer作成
	CreateBuffer();

	// パーティクル初期化
	particle_->Init();
}


/// <summary>
/// 更新処理
/// </summary>
template<typename T>
inline void IEmitter<T>::Update()
{
	// パーティクル更新
	particle_->Update();

	// 射出更新
	Update_ConfigData();

	// 乱数シード更新
	Update_RandomSeedData();

	// データ書き込み
	WriteData();

	// 発生処理
	Emit();
}


/// <summary>
/// 描画処理
/// </summary>
template<typename T>
inline void IEmitter<T>::Draw3D()
{
	// パーティクル描画
	particle_->Draw();
}


/// <summary>
/// 発生
/// </summary>
template<typename T>
inline void IEmitter<T>::Emit()
{
	// Commandの取得
	Commands commands = CommandManager::GetInstance()->GetCommands();

	// PipeLineCheck
	PipeLineManager::SetPipeLine(PipeLine::Container::Compute, pipeLine_Category, pipeLine_SubFileter);

	// Particle
	particle_->Bind_ParticleProp(0);

	// FreeList
	particle_->Bind_FreeList(1);

	// FreeListIndex
	particle_->Bind_FreeListIndex(2);

	// Emitter
	emitBuff_.BindComputeCBV(3);

	// Range
	rangeBuff_.BindComputeCBV(4);

	// EmitConfig
	configBuff_.BindComputeCBV(5);

	// RandomSeed
	randSeedBuff_.BindComputeCBV(6);

	// Dispatch
	commands.List->Dispatch(1, 1, 1);

	// Barrierを張る
	particle_->SetUAVBarrier();

}


/// <summary>
/// Data生成
/// </summary>
template<typename T>
inline void IEmitter<T>::CreateData()
{
	// Particle
	particle_ = std::make_unique<GPUParticle>();
	// Emitter
	emitData_ = std::make_shared<T>();
	// Range
	rangeData_ = std::make_shared<Emitter::EmitRange>();
	// Congig
	configData_ = std::make_shared<Emitter::EmitConfig>();
	// RandomSeed
	randSeedData_ = std::make_shared<Emitter::RandomSeed>();
	randSeedData_->gameTime = timeSys_->Get_SinceStart();
	randSeedData_->dynamicTime = RandomGenerator::getRandom(Scope(0.0f, 1000.0f));
}


/// <summary>
/// Buffer生成
/// </summary>
template<typename T>
inline void IEmitter<T>::CreateBuffer()
{
	// Emitter
	emitBuff_.CreateCBV();
	// Range
	rangeBuff_.CreateCBV();
	// Congig
	configBuff_.CreateCBV();
	// RandomSeed
	randSeedBuff_.CreateCBV();

}


/// <summary>
/// 射出データの更新
/// </summary>
template<typename T>
inline void IEmitter<T>::Update_ConfigData()
{
	configData_->elapsedTime -= 1.0f / 60.0f; // 減算

	// タイマー0以下で
	// 射出許可 & タイマーリセット
	if (configData_->elapsedTime <= 0.0f) {
		// タイマーリセット
		configData_->elapsedTime = configData_->spawnInterval;
		configData_->isEmitting = true;
	}
	else {
		configData_->isEmitting = false;
	}
}


/// <summary>
/// 乱数シードデータの更新
/// </summary>
template<typename T>
inline void IEmitter<T>::Update_RandomSeedData()
{
	// ゲーム開始からの時間を取得
	randSeedData_->gameTime = timeSys_->Get_SinceStart();

	// 初期乱数値 + 開始からの時間
	randSeedData_->dynamicTime = RandomGenerator::getRandom(Scope(0.0f, 1000.0f));
	randSeedData_->dynamicTime += randSeedData_->gameTime;

	// 600秒（10分）ごとにリセット
	if (randSeedData_->gameTime - lastResetTime_ >= 600.0f) {
		randSeedData_->dynamicTime = RandomGenerator::getRandom(Scope(0.0f, 1000.0f));
		lastResetTime_ = randSeedData_->gameTime;
	}
}


/// <summary>
/// Bufferへデータ書き込み
/// </summary>
template<typename T>
inline void IEmitter<T>::WriteData()
{
	// Emitter
	emitBuff_.UpdateData(emitData_.get());

	// range
	rangeBuff_.UpdateData(rangeData_.get());

	// config
	configBuff_.UpdateData(configData_.get());

	// randomSeed
	randSeedBuff_.UpdateData(randSeedData_.get());
}
