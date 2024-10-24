#pragma once

#include "CommandManager/CommandManager.h"
#include "../IParticle.h"
#include "PipeLineManager/PipeLineManager.h"
#include "CreateResource/CreateResource.h"
#include "DescriptorManager/DescriptorManager.h"
#include "View/SRVManager/SRVManager.h"
#include "Math/MyMath.h"
#include "Math/Struct.h"
#include "GameObject/Camera/Camera.h"
#include "GameObject/Camera/Manager/CameraManager.h"
#define INSTANCE_MAX 1000;


/* ParticleSystemクラス */
class ParticleSystem {

public: // メンバ関数

	// コンストラクタとデストラクタ
	ParticleSystem() {};
	~ParticleSystem() {};

	// 初期化処理、更新処理、描画処理
	void Initialize();
	void Draw(list<ParticleProperties> prope);

#pragma region Get 取得

	// テクスチャの取得
	uint32_t GetUseTexture() { return this->useTexture_; }

#pragma endregion 

#pragma region Set 取得

	// テクスチャの設定
	void SetUseTexture(uint32_t setTexture) { this->useTexture_ = setTexture; }

#pragma endregion 


private: // メンバ関数

	// コマンドコール
	void CommandCall();

	// ビルボードの処理
	Matrix4x4 CalcBillBord();


private: // メンバ変数

	// リソース
	ResourcePeroperty resource_{};

	// 
	uint32_t dsvIndex_ = 0;

	// インスタンスの最大と個数
	const uint32_t kMaxInstanceNum_ = INSTANCE_MAX;
	uint32_t instanceNum_;


	Vector4 pos_ = { 0.0f, 0.0f, 0.0f, 1.0f };
	float size_ = 0.5f;

	// 使用するテクスチャ
	uint32_t useTexture_;
};

