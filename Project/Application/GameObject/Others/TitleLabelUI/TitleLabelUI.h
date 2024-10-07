#pragma once

#include "GameObject/GameObject.h"
#include "GameObject/IObject/IObject.h"


// Labelの種類
enum class TitleLabelType {
	Start,
	Exsit,
	Count,
};

/* TitleLabelUIクラス */
class TitleLabelUI {

public:

	// コンストラクタ、デストラクタ
	TitleLabelUI() = default;
	~TitleLabelUI() = default;

	// 初期化処理　更新処理　描画処理
	void Init();
	void Update();
	void Draw3D();
	void Draw2DFront();
	void Draw2DBack();


private:


};

