#pragma once

#include "../../BufferResource/BufferResource.h"
#include "../../CommandManager/CommandManager.h"
#include "../../View/SRVManager/SRVManager.h"
#include "../../Transform/Transform.h"
#include "../../PipeLineManager/PipeLineManager.h"

#include "../Resources/GPUParticleResources.h"

#include "GameObject/GameObject.h"
#include "Math/MyMath.h"


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
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(std::vector<Transform>& transforms, const std::vector<MaterialDataN>& materials);


private:

	/// <summary>
	/// コマンドコール
	/// </summary>
	void CommandCall_Init();
	void CommandCall_Update();
	void CommandCall_Draw();

	/// <summary>
	/// BufferResourceの作成
	/// </summary>
	void CreateBufferResource();


private:

	// カメラマネージャー
	CameraManager* cameraManager_ = nullptr;

	// バッファーに書き込むデータ
	GPUParticleDatas datas_{};

	// バッファー
	GPUParticleResources buffers_{};

	// パーティクルのインスタンス数
	uint32_t instanceNum_ = 0;

	// 使用するモデル
	//std::unique_ptr<Model> model_;



};

