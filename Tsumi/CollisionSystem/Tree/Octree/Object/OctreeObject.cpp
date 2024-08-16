#include "OctreeObject.h"
#include "../Cell/OctreeCell.h"



// 空間に登録する
void OctreeObject::RegisterCell(OctreeCell* cell)
{
	this->cell_ = cell;
}


// 空間から削除する
bool OctreeObject::Remove()
{
	// 既に逸脱している場合は早期return
	if (cell_ == nullptr) return false;
	
	// 空間に通知
	if (!cell_->OnRemove(this)) return false;

	// リンクくの切断
	if (preObj_) {
		preObj_->nextObj_ = nextObj_;
	}
	if (nextObj_) {
		nextObj_->preObj_ = preObj_;
	}

	// 自身のポインタをnullにして安全にする
	cell_ = nullptr;
	preObj_ = nullptr;
	nextObj_ = nullptr;
	
	return true;
}
