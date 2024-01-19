#pragma once
#include "MyMath.h"
#include "Struct.h"
#include "IParticleState.h"
#include "ParticleGraphicPipeline.h"
#include "CreateResource.h"
#include "DescriptorManager.h"


/* ParticlePlaneクラス */
class ParticlePlane : public IParticleState {

public: // メンバ関数

	ParticlePlane() {};
	~ParticlePlane() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(Particle* pParticle) override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(Particle* pParticle, list<ParticleProperties> prope , ViewProjection view) override;


private: // メンバ関数

	/// <summary>
	/// コマンドコール
	/// </summary>
	void CommandCall(uint32_t texHandle);


private: // メンバ変数

	// リソース
	ResourcePeroperty resource_{};

	// ModelData
	ModelData modelData_{};

	Vector4 pos_ = { 0.0f, 0.0f, 0.0f, 1.0f };
	float size_ = 0.5f;

	int instanceCount_;
	uint32_t NumInstance_;

	uint32_t itrNum_ = 0;

	uint32_t dsvIndex_ = 0;
};

