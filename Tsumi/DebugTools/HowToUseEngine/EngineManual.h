#pragma once

#include "GameObject.h"

#include "Cloud/Cloud.h"
#include "MonsBall/MonsBall.h"
#include "Photon/Photon.h"
#include "BGM/BGM.h"


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

	// 雲模様背景
	unique_ptr<Cloud> cloudBG_ = nullptr;

	// モンスターボール
	unique_ptr<MonsBall> monsBall_ = nullptr;

	// 光子パーティクル
	unique_ptr<Photon> photon_ = nullptr;

	// BGM
	unique_ptr<BGM> bgm_ = nullptr;



	// スプライト
	unique_ptr<Sprite> uvSp_ = nullptr;

	// テクスチャハンドル
	uint32_t uvTexHD_;

	// ワールドトランスフォーム
	WorldTransform uvWt_{};
};
