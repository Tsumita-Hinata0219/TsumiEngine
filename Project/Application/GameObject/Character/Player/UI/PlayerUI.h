#pragma once

#include <list>
#include <memory>

#include "../../../IObject/IObject.h"
#include "../../../GameObject.h"


// UIの種類
enum class PlayerUIType {
	Shooting,
	Moving,
	Camera,
	Count,
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
	std::vector<SpriteProperty> ui_;
};

