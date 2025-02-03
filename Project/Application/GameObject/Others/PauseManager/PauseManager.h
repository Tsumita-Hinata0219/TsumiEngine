#pragma once


/* ポーズマネージャー */
class PauseManager {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PauseManager() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PauseManager() = default;

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
	void Draw2DBack();


#pragma region Accessor

	// ポーズ中かどうか
	bool IsPause() const { return m_isPause; }
	void SetIsPause(bool isPause) { m_isPause = isPause; }

#pragma endregion 

private:


private:

	// ポーズ中かどうか
	bool m_isPause = false;


};
