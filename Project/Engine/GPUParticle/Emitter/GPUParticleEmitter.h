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

	/// <summary>
	/// データファイルの読み込み
	/// </summary>
	//void LoadScriptFile(const std::string& rootPath, const std::string& fileName);


#pragma region Accessor

	// Emitter
	const std::weak_ptr<T> GetEmitData() { return this->emitterData_; }

	// Emitter Config
	const std::weak_ptr<GpuEmitter::EmitterConfig> GetEmitConfig() { return this->emitConfigData_; }

	// Emitter Range
	const std::weak_ptr<GpuEmitter::EmitterRange> GetEmitRange() { return this->emitterRangeData_; }

#pragma endregion 


private:

	/// <summary>
	/// タイマー更新
	/// </summary>
	void TimeUpdate();

	/// <summary>
	/// シードの更新
	/// </summary>
	void UpdateRandomSeed();

	/// <summary>
	/// Bufferへデータの書き込み
	/// </summary>
	void WriteData();

	/// <summary>
	/// ImGuiの描画
	/// </summary>
	//void DrawImGui(std::string label = "");


private:

	// パーティクルのPtr
	std::weak_ptr<GPUParticle> particlePtr_;

	// 射出関連
	std::shared_ptr<GpuEmitter::EmitterConfig> emitConfigData_;
	BufferResource<GpuEmitter::EmitterConfig> emitConfigBuffer_;

	// Emitter
	std::shared_ptr<T> emitterData_;
	BufferResource<T> emitterBuffer_;

	// 範囲関連
	std::shared_ptr<GpuEmitter::EmitterRange> emitterRangeData_;
	BufferResource<GpuEmitter::EmitterRange> emitterRangeBuffer_;

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

	// 射出関連データ作成
	emitConfigData_ = std::make_shared<GpuEmitter::EmitterConfig>();
	// 射出関連データのバッファー作成
	emitConfigBuffer_.CreateCBV();

	// Emitterデータ作成
	emitterData_ = std::make_shared<T>();
	// Emitterデータのバッファー作成
	emitterBuffer_.CreateCBV();

	// Rangeデータ作成
	emitterRangeData_ = std::make_shared<GpuEmitter::EmitterRange>();
	// Range関連データのバッファー作成
	emitterRangeBuffer_.CreateCBV();

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
	// シードデータの更新
	UpdateRandomSeed();

	// タイマー更新
	TimeUpdate();

#ifdef _DEBUG
	//DrawImGui();
#endif // _DEBUG

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
	PipeLineManager::SetPipeLine(PipeLine::Container::Compute, PipeLine::Category::EmitterSphere);

	// Particle
	particlePtr_.lock()->Bind_ParticleProp(0);

	// FreeList
	particlePtr_.lock()->Bind_FreeList(1);

	// FreeListIndex
	particlePtr_.lock()->Bind_FreeListIndex(2);

	// Emitter
	emitterBuffer_.BindComputeCBV(3);

	// EmitterRange
	emitterRangeBuffer_.BindComputeCBV(4);

	// EmitterConfig
	emitConfigBuffer_.BindComputeCBV(5);

	// RandomSeed
	seedBuffer_.BindComputeCBV(6);

	// Dispach
	commands.List->Dispatch(1, 1, 1);

	// Barrierを張る
	particlePtr_.lock()->SetUAVBarrier();
}


///// <summary>
///// データファイルの読み込み
///// </summary>
//template<typename T>
//inline void GPUParticleEmitter<T>::LoadScriptFile(const std::string& rootPath, const std::string& fileName)
//{
//
//
//
//}


/// <summary>
/// タイマー更新
/// </summary>
template<typename T>
inline void GPUParticleEmitter<T>::TimeUpdate()
{
	emitConfigData_->elapsedTime -= 1.0f / 60.0f; // δタイムを加算
	// 射出間隔を上回ったら射出許可を出して時間を調整
	if (emitConfigData_->elapsedTime <= 0.0f)
	{
		// 次の射出間隔を設定
		emitConfigData_->elapsedTime = emitConfigData_->spawnInterval;
		emitConfigData_->isEmitting = true;

		// パーティクルを沸かせる
		//Emit();
	}
	else {
		emitConfigData_->isEmitting = false;
	}
}


/// <summary>
/// シードの更新
/// </summary>
template<typename T>
inline void GPUParticleEmitter<T>::UpdateRandomSeed()
{
	// ゲーム開始からの時間を取得
	seedData_.gameTime = timeSys_->Get_SinceStart();
	// 初期乱数値 + 開始からの時間
	seedData_.dynamicTime = RandomGenerator::getRandom(Scope(0.0f, 1000.0f));
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
	// EmitterConfig
	emitConfigBuffer_.UpdateData(emitConfigData_.get());

	// Emitter
	emitterBuffer_.UpdateData(emitterData_.get());

	// EmitterRange
	emitterRangeBuffer_.UpdateData(emitterRangeData_.get());

	// SeedData
	seedBuffer_.UpdateData(&seedData_);
}


///// <summary>
///// ImGuiの描画
///// </summary>
//template<typename T>
//inline void GPUParticleEmitter<T>::DrawImGui(std::string label)
//{
//	if (ImGui::TreeNode((label + "Emitter"))) {
//
//	}
//}
