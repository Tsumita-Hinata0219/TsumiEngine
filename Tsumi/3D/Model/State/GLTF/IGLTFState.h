#pragma once

#include "../ModelState.h"


/* GLTFState */
class IGLTFState : public ModelState {

public:

	// コンストラクタ、デストラクタ
	IGLTFState() { stateType = GLTF; };
	~IGLTFState() {};

	// 描画処理
	void Draw(Transform transform) override;

	// コマンドコール
	void CommandCall() override;

private:


};
