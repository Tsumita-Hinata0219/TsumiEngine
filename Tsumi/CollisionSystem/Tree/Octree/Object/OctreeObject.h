#pragma once

#include "../../../Shape/CollisionShape.h"
#include "../../../Component/CollisionComponent.h"

#include <memory>
#include <vector>


// 前方宣言
class OctreeCell;


/* 八分木に登録するオブジェクトの情報を保持するクラス */
class OctreeObject {

public:

	// コンストラクタ、デストラクタ
	OctreeObject() {};
	~OctreeObject() {};

	// パラメータ付きコンストラクタ
	OctreeObject(OctreeCell* cell, CollisionShape* shape) : cell(cell), shape(shape) {};

	// 空間に登録する
	void RegisterCell(OctreeCell* cell);

	// 空間から削除する
	bool Remove();


public:

	// 登録空間
	OctreeCell* cell = nullptr;

	// 判定対象オブジェクト
	CollisionShape* shape = nullptr;

	// 前のオブジェクトへのポインタ
	OctreeObject* preObj = nullptr;

	// 次のオブジェクトへのポインタ
	OctreeObject* nextObj = nullptr;

};

