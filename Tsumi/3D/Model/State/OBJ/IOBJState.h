#pragma once

#include "../ModelState.h"


/* OBJState */
class IOBJState : ModelState {

public:

	// コンストラクタ、デストラクタ
	IOBJState() { stateType = OBJ; };
	~IOBJState() {};

	// 描画処理
	void Draw() override;

	// コマンドコール
	void CommandCall() override;

private:


};

