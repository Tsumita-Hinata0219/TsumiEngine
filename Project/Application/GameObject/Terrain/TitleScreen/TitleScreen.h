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

	// 衝突判定コールバック関数
	void onCollision([[maybe_unused]] IObject* object) override;


private:

	// カーソルの移動処理
	void CurSorMove();
	void KeyMove();
	void PadMove();

	// 加算姿勢の計算
	void CalcAddRotate();

	// スクリーンの姿勢計算
	void CalcScreenRotate();


private:

	// Inputクラス
	Input* input_ = nullptr;

	// ScreenModel
	std::unique_ptr<Model> screenModel_;
	Transform screenTrans_{};
	Transform pTrans_{};
	
	// カーソルスプライト
	uint32_t cursorTexHD_;
	std::unique_ptr<Sprite> cursorSprite_;
	WorldTransform cursorTrans_;

	// 移動速度
	Vector3 velocity_{};
	float cursorSpeed_ = 0.0f;

	//Stickの入力を取得
	Vector2 L_StickInput_{};
	Vector2 R_StickInput_{};

	// 加算姿勢
	Vector2 addRotate_{};
	std::pair<Vector2, Vector2> rangeInput_{};
	Vector2 rangeOutput_{};
};
