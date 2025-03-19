#pragma once

#include "Math/MyMath.h"
#include "../Structure/RenderStructure.h"


// 前方宣言
// CameraManager
class CameraManager;
// PipeLineManager
class PipeLineManager;


namespace RenderSystem {

class RenderState {

private:

	// 描画に必要なDeta
	std::unique_ptr<RenderSystem::Rendering::Datas> datas_;

	// GPUに送るBuffer
	std::unique_ptr<RenderSystem::Rendering::Buffers> buffers_;

	// CameraManager
	CameraManager* cameraManager_ = nullptr;
	// PipeLineManager
	PipeLineManager* pipeLine_ = nullptr;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	RenderState();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~RenderState() = default;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw3D();


private:

	/// <summary>
	/// Buffer生成
	/// </summary>
	void Create_RenderBuffer();

	/// <summary>
	/// 描画データの更新
	/// </summary>
	void Update_RenderData();

	/// <summary>
	/// PipeLineのチェック
	/// </summary>
	void Check_PipeLine();

	/// <summary>
	/// 描画データのバインド
	/// </summary>
	void Bind_RenderData();

	/// <summary>
	/// 描画
	/// </summary>
	void Execute_DrawCommand();


};

}