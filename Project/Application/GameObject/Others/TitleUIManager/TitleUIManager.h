#pragma once

#include "GameObject/GameObject.h"
#include "GameObject/IObject/IObject.h"

#include "GameNameBar/GameNameBar.h"
#include "TitleLabelObject/TitleLabelObject.h"


// Labelの種類
enum class TitleLabelType {
	Start,
	Exsit,
	Count,
};


/* TitleUIManagerクラス */
class TitleUIManager {

public:

	// コンストラクタ、デストラクタ
	TitleUIManager() = default;
	~TitleUIManager() = default;

	// 初期化処理　更新処理　描画処理
	void Init();
	void Update();
	void Draw3D();
	void Draw2DFront();
	void Draw2DBack();


private:

	// ゲーム名
	std::unique_ptr<GameNameBar> gameName_;

	// ラベル
	std::vector<std::unique_ptr<TitleLabelObject>> labelObjs_;

	// ラベルのBase座標
	Vector3 labelBasePos_{};
	// オフセット
	Vector3 labelOffset_{};
	// スタートラベルの座標
	Vector3 startLabelPos_{};
	// 終了ラベルの座標
	Vector3 exsitLabelPos_{};

};

