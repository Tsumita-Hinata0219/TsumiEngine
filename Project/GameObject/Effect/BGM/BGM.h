#pragma once

#include "GameObject.h"

class BGM {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	BGM() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BGM();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ViewProjection view);


private:

	// オーディオハンドル
	uint32_t kakkoiiAudioHD_;

	// 音量
	float volume_;

	// 再生中か
	bool AudioIsPlaying_;

	// テクスチャハンドル
	uint32_t AudioTexHD_;
	uint32_t isStateTexHD_[2];
	uint32_t volumeTexHD_;

	// スプライト
	unique_ptr<Sprite> AudioS_ = nullptr;
	unique_ptr<Sprite> isStateS_[2] = { nullptr };
	unique_ptr<Sprite> volumeS_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform AudioWt_{};
	WorldTransform isStateWt_[2]{};
	WorldTransform volumeWt_{};
	
};

