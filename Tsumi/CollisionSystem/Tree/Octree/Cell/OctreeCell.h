#pragma once

#include <iostream>
#include "../Object/OctreeObject.h"


// 前方宣言
class OctreeObject;


// OctreeCellクラス
class OctreeCell {

public:

	// コンストラクタ、デストラクタ
	OctreeCell() {}
	~OctreeCell() {}

	// オブジェクトを空間に登録する
	bool Push(OctreeObject* setObj);

	// オブジェクトが削除された時の処理
	bool OnRemove(OctreeObject* reObj);

public:

	// 空間内の最新のオブジェクト
	OctreeObject* obj = nullptr;

};


