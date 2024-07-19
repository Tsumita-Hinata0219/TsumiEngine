#pragma once

#include "../GameObject.h"
#include "../../Tsumi/3D/Model/Model.h"
#include "../../Tsumi/3D/Model/ModelManager/ModelManager.h"
#include "../../Tsumi/Transform/Transform.h"

/* ゲームオブジェクトの基底クラス */
class IBaseObject {

public: // メンバ関数

	// デストラクタ
	virtual ~IBaseObject() {};

	// 初期化、更新、描画
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw3D() = 0;
	virtual void Draw2DFront() = 0;
	virtual void Draw2DBack() = 0;


#pragma region Accessor アクセッサ

	// ワールドポジションの取得
	Vector3 GetWorldPosition() { return this->transform_.GetWorldPos(); }


#pragma endregion 


private:



protected: // メンバ変数

	// モデル
	std::unique_ptr<Model> model_;

	// トランスフォーム
	Transform transform_{};
};
