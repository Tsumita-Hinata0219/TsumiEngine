#pragma once

#include "../Resources/ParticleResources.h"
#include "../Particle/GPUParticle.h"


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


#pragma region Accessor

	// エミッターデータの設定
	void SetEmitData(const T& setData) { this->emitterData_ = setData; }


#pragma endregion 


private:

	// 書き込み用のバッファー
	BufferResource<T> writeBuffer_;

	// エミッターデータ
	T emitterData_;
};



/// <summary>
/// 生成
/// </summary>
template<typename T>
inline void GPUParticleEmitter<T>::Create(std::unique_ptr<GPUParticle>& particle)
{

}


/// <summary>
/// 更新処理
/// </summary>
template<typename T>
inline void GPUParticleEmitter<T>::Update()
{
}


/// <summary>
/// Particleを沸かせる
/// </summary>
template<typename T>
inline void GPUParticleEmitter<T>::Emit(std::unique_ptr<GPUParticle>& particle)
{



}

