#pragma once

#include <list>
#include <memory>

#include "../../../IObject/IObject.h"
#include "../../../GameObject.h"


// UIの種類
enum class PlayerUIType {
	Shooting,
	Count,
};
// UIの描画に必要なもの
struct UIProperty {
	std::unique_ptr<Sprite> sprite;
	WorldTransform transfrom;
	uint32_t texture = 0;
};
enum class U {
	shot,
	hp,
	Count
};


/* プレイヤー関連のUI */
class PlayerUI {

public:

	// コンストラクタ、デストラクタ
	PlayerUI() = default;
	~PlayerUI() = default;

	// 初期化処理、更新処理、描画処理
	void Init();
	void Update();
	void Draw2DFront();
	void Draw2DBack();


private:

	// UIの描画
	void DrawUI(int type);


private:

	// UI
	std::vector<UIProperty> ui_;
};

