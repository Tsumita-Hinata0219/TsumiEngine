#pragma once

#include "../ModelState.h"


/* GLTFState */
class IGLTFState : public ModelState {

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
