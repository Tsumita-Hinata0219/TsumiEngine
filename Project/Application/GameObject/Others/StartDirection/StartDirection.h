#pragma once

#include <list>
#include <memory>

#include "../../IObject/IObject.h"
#include "../../GameObject.h"

/* StartDirectionクラス */
class StartDirection {

public:

	// コンストラクタ、デストラクタ
	StartDirection() = default;
	~StartDirection() = default;

	// 初期化処理、更新処理、描画処理
	void Init();
	void Update();
	void Draw2DFront();


private:

	// サイズの移行処理
	void SizeFunc();

	// 姿勢の移行処理
	void RotateFunc();


private:

	// texture
	std::vector<uint32_t> textures_;
	uint32_t texArrayNum_ = 0;

	// Sprite
	std::unique_ptr<Sprite> sprite_;
	Vector2 texSize_{};

	// Transform
	Transform trans_{};
};

