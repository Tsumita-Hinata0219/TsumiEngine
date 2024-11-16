#pragma once

#include "GameObject/GameObject.h"
#include "Math/MyMath.h"

#include "BackScreen/ClearDirectionBackScreen.h"


/* クリア演出のクラス */
class ClearDirectionManager {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ClearDirectionManager() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ClearDirectionManager() = default;

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


private:

	// BackScreen
	std::unique_ptr<ClearDirectionBackScreen> backScreen_;


};

