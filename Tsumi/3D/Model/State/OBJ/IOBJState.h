#pragma once

#include "../ModelState.h"


/* OBJState */
class IOBJState : public ModelState {

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

