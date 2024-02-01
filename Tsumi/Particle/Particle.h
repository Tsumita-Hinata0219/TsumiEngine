#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "IParticleState.h"
#include "ParticlePlane.h"
#include "MyMath.h"


/* Particleクラス */
class Particle {

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Particle() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Particle() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="state"></param>
	void Initialize(IParticleState* state, uint32_t instanceNum);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ViewProjection view);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// リストの登録
	/// </summary>
	void PushBackParticles(ParticleProperties prope);


#pragma region Get 取得

	/// <summary>
	/// インスタンス数の取得
	/// </summary>
	uint32_t GetInstanceNum() { return instanceNum_; }

	/// <summary>
	/// 使用するテクスチャハンドルの取得
	/// </summary>
	uint32_t GetUseTexture() { return this->useTexture_; }

	/// <summary>
	/// 何かのサイズの取得
	/// </summary>
	float GetSize() { return this->size_; }

#pragma endregion

#pragma region Set 設定

	/// <summary>
	/// テクスチャハンドルの設定
	/// </summary>
	void SetTexHandle(uint32_t texHD) { this->useTexture_ = texHD; }

#pragma endregion 


private: // メンバ関数

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();


private: // メンバ変数

	// ステートパターン
	IParticleState* state_ = nullptr;

	// パーティクルリスト
	std::list<ParticleProperties> particlePropes_{};

	// インスタンス数
	uint32_t instanceNum_;

	// テクスチャ
	uint32_t useTexture_;

	// サイズ
	float size_;

	// Δタイム
	const float kDeltaTimer = 1.0f / 60.0f;

};

