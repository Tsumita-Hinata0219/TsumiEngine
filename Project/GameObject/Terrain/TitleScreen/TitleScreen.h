#pragma once

#include "../../IObject/IObject.h"
#include "../../GameObject.h"

class TitleScreen : public IObject {

public: // メンバ関数

	// コンストラクタとデストラクタ
	TitleScreen() {};
	~TitleScreen() {};

	// 初期化処理　更新処理　描画処理
	void Init() override;
	void Update() override;
	void Draw3D() override;
	void Draw2DFront() override;
	void Draw2DBack() override;


private:

	// ScreenModel
	std::unique_ptr<Model> screenModel_;

	// Transform
	Transform trans_{};

	// カーソルスプライト
	uint32_t cursorTexHD_;
	std::unique_ptr<Sprite> cursorSprite_;
	WorldTransform cursorTrans_;


	// ScreenModel
	std::unique_ptr<Model> testModel_;

	// Transform
	Transform ttrans_{};

};
