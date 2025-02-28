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
	void Init(uint32_t instanceNum = 1);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// パーティクルの要素のバインド
	/// </summary>
	void Bind_ParticleProp(UINT num);

	/// <summary>
	/// フリーカウンターのバインド
	/// </summary>
	void Bind_FreeCounter(UINT num);

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
	void Bind_Update();
	void Bind_Draw();

	/// <summary>
	/// BufferResourceの作成
	/// </summary>
	void CreateBufferResource();


private:

	// カメラマネージャー
	CameraManager* cameraManager_ = nullptr;

	// パーティクルのインスタンス数
	uint32_t instanceNum_ = 0;
	const uint32_t minInstanceNum_ = 1024; // 最低数

	// パーティクルの要素
	GpuParticle::ModelData modelData_{};
	GpuParticle::ResourceHandles handles_{};

	// フリーカウンター
	BufferResource<uint32_t> freeCounterBuffer_;

	// 使用するモデル
	std::unique_ptr<Model> model_;
};

