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
	void Update();

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

	// スプライト
	std::unique_ptr<Sprite> spriteFront_ = nullptr;
	WorldTransform spriteFrontTrans_{};
	std::unique_ptr<Sprite> spriteBack_ = nullptr;
	WorldTransform spriteBackTrans_{};

	// Obj
	std::unique_ptr<Model> modelObj_ = nullptr;
	WorldTransform modelTrans_{};


	// texHandle
	uint32_t uvCheckerHD_;
	uint32_t monsterBallHD_;
	uint32_t asanohaHD_;
	uint32_t skyHD_;


	// SoundHandle
	uint32_t mokugyoHD_;
	uint32_t kakkoiiHD_;


	int bgmStartTimer = 0;

};
