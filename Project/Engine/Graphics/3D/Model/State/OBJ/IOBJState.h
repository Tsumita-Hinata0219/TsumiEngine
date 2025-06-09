#pragma once

#include "../IModelState.h"


/* OBJState */
class IOBJState : public IModelState {

public:

	// コンストラクタ、デストラクタ
	IOBJState() {};
	IOBJState(ModelDatas datas);
	~IOBJState() {};

	// 描画処理
	void Draw(Transform& transform) override;

	// コマンドコール
	void CommandCall() override;

private:


};

