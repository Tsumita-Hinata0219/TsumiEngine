#pragma once

#include "../ModelState.h"


/* GLTFState */
class IGLTFState : ModelState {

public:

	// コンストラクタ、デストラクタ
	IGLTFState() { stateType = GLTF; };
	~IGLTFState() {};

	// 描画処理
	void Draw() override;

	// コマンドコール
	void CommandCall() override;

private:


};
