#pragma once

#include "GameObject/GameObject.h"


// 前方宣言
class PauseManager;


/* ポーズ時の描画クラス */
class PauseRenderer {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PauseRenderer() = default;
	PauseRenderer(PauseManager* pauseManager) : m_pauseManager_(pauseManager) {}

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PauseRenderer() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw2DFront();

	/// <summary>
	/// ポーズをかける
	/// </summary>
	void InPause();

	/// <summary>
	/// ポーズを解除する
	/// </summary>
	void OutPause();


private:

	/// <summary>
	/// BackのAlphaの計算
	/// </summary>
	void CalcBackAlpha();


private:

	// ポーズマネージャー
	PauseManager* m_pauseManager_ = nullptr;

	// Back
	std::unique_ptr<Sprite> m_BackSprite_;
	Transform m_BackTransform_{};
	Vector4 m_BackColor_{};
	float m_BackUnPauseAlpha_ = 0.0f;
	float m_BackPauseAlpha_ = 0.0f;
	std::pair<float, float> m_BackCalcAlpha_{};
}; 
