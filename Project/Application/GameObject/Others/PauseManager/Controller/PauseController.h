#pragma once


/* ポーズ時の操作クラス */
class PauseController
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PauseController() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PauseController() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

private:

};
