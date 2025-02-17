#pragma once

#include "GameObject/GameObject.h"


class StageSelectOperation;

class StageSelectNavigation {
public:
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	StageSelectNavigation() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StageSelectNavigation() = default;

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

	// オペレーションクラスのセット
	void SetOperation(StageSelectOperation* setPtr) { this->pOperation_ = setPtr; }


private:

	StageSelectOperation* pOperation_;

	std::vector<std::unique_ptr<Sprite>> sprites_;
	std::vector<uint32_t> textures_;
	Transform trans_{};

};
