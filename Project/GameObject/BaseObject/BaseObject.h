#pragma once

#include "../GameObject.h"

/* ゲームオブジェクトの基底クラス */
class IBaseObject {

public: // メンバ関数

	// デストラクタ
	virtual ~IBaseObject() {};

	// 初期化、更新、描画
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;


private:



protected: // メンバ変数



};
