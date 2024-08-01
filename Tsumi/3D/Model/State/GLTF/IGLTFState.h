#pragma once

#include "../ModelState.h"


/* GLTFState */
class IGLTFState : public ModelState {

public:

	// コンストラクタ、デストラクタ
	IGLTFState() {};
	IGLTFState(ModelDatas datas);
	~IGLTFState() {};

	// 描画処理
	void Draw(Transform transform) override;

	// コマンドコール
	void CommandCall() override;

private:


};
