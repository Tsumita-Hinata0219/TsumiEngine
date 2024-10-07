#pragma once

#include "GameObject/GameObject.h"


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

	// 初期化、更新、描画
	void Init();
	void Update();
	void Draw3D();


private:


};

