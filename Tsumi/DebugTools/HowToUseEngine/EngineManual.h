#pragma once

#include "GameObject.h"


/* EngineManualクラス */
class EngineManual {

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EngineManual() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EngineManual();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(ViewProjection view);

	/// <summary>
	/// 背景スプライトの描画処理
	/// </summary>
	void BackSpriteDraw(ViewProjection view);

	/// <summary>
	/// ３Dオブジェクトの描画処理
	/// </summary>
	void ModelDraw(ViewProjection view);

	/// <summary>
	/// 前景スプライトの描画処理
	/// </summary>
	void FrontSpriteDraw(ViewProjection view);


private: // メンバ関数

	/// <summary>
	/// Audioに関する処理まとめたやつ
	/// </summary>
	void AudioUpdate();

private: // メンバ変数

	// Particle
	std::unique_ptr<Particle> particle_ = nullptr;
	static constexpr uint32_t NumInstance_ = 10;
	ParticleProperties particlePrope_[NumInstance_]{};

	uint32_t uvCheckerHD_;
};
