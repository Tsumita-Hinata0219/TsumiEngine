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
	PauseRenderer(PauseManager* pauseManager) : m_pauseManager(pauseManager) {}

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

private:

	// ポーズマネージャー
	PauseManager* m_pauseManager = nullptr;


};
