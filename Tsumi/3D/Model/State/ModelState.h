#pragma once

#include "../../../BufferResource/BufferResource.h"
#include "../../../CommandManager/CommandManager.h"
#include "../../../View/SRVManager/SRVManager.h"
#include "../../../Transform/Transform.h"
#include "../../../PipeLineManager/PipeLineManager.h"


enum StateType {
	NONE,
	OBJ,
	GLTF,
};


// Modelの前方宣言
class Model;


/* ModelState モデルのステートパターン */
class ModelState {

public: // メンバ変数

	// デストラクタ
	virtual ~ModelState() {};

	// 描画処理
	virtual void Draw() = 0;
	
	// コマンドコール
	virtual void CommandCall() = 0;


protected: // メンバ変数

	StateType stateType = NONE;
};