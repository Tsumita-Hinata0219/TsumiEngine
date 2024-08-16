#include "OctreeObject.h"
#include "../Cell/OctreeCell.h"



// 空間に登録する
void OctreeObject::RegisterCell(OctreeCell* setCell)
{
	this->cell = setCell;
}


// 空間から削除する
bool OctreeObject::Remove()
{
	// 既に逸脱している場合は早期return
	if (cell == nullptr) return false;
	
	// 空間に通知
	if (!cell->OnRemove(this)) return false;

	// リンクくの切断
	if (preObj) {
		preObj->nextObj = nextObj;
	}
	if (nextObj) {
		nextObj->preObj = preObj;
	}

	// 自身のポインタをnullにして安全にする
	cell = nullptr;
	preObj = nullptr;
	nextObj = nullptr;
	
	return true;
}
