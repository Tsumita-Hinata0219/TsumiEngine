#pragma once

#include "BufferResource/BufferResource.h"
#include "CommandManager/CommandManager.h"
#include "Transform/Transform.h"
#include "PipeLineManager/PipeLineManager.h"

#include "../Resources/ParticleResources.h"

#include "Math/MyMath.h"


// 前方宣言
class CameraManager;
class Model;


/* GPUParticleクラス */
class GPUParticle {

public:

	/// <summary>
	/// コンストラクト
	/// </summary>
	GPUParticle() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GPUParticle() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="instanceNum">インスタンス数</param>
	void Init(uint32_t instanceNum = 0);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(std::vector<Transform>& transforms, const std::vector<MaterialDataN>& materials);

	/// <summary>
	/// パーティクルの要素のバインド
	/// </summary>
	void Bind_ParticleProp();


#pragma region Accessor アクセッサ

	/// <summary>
	/// インスタンシング数
	/// </summary>
	uint32_t GetInstanceNum() const { return instanceNum_; }


#pragma endregion 


private:

	/// <summary>
	/// バインド
	/// </summary>
	void Bind_Init();
	void Bind_Draw();

	/// <summary>
	/// BufferResourceの作成
	/// </summary>
	void CreateBufferResource();


private:

	// カメラマネージャー
	CameraManager* cameraManager_ = nullptr;

	// バッファーに書き込むデータ
	GpuParticle::ModelData modelData_{};

	// バッファー
	GpuParticle::ResourceHandles handles_{};

	// パーティクルのインスタンス数
	uint32_t instanceNum_ = 0;

	// 使用するモデル
	std::unique_ptr<Model> model_;
};

