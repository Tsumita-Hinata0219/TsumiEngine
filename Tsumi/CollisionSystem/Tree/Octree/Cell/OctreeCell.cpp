#include "OctreeCell.h"



// オブジェクトを空間に登録する
bool OctreeCell::Push(OctreeObject* setObj)
{
	// 無効なオブj稀有とは登録しない
	if (setObj == nullptr) return false;

	// 既に登録されている空間と比較して、二重登録をチェック
	if (setObj->cell == this) return false;

	// 新規登録
	if (obj == nullptr) {
		obj = setObj;
	}
	else {
		// 最新のオブジェクトを登録
		setObj->nextObj = obj;
		obj->preObj = setObj;
		obj = setObj;
	}

	// 空間にオブジェクトを登録
	setObj->RegisterCell(this);

	return true;
}


// オブジェクトが削除された時の処理
bool OctreeCell::OnRemove(OctreeObject* reObj)
{
	// 最新のオブジェクトが削除された場合、次のオブジェクトに変更
	if (obj == reObj) {
		obj = reObj->nextObj;
	}

	// 空間からの削除に関する追加処理(必要に応じて実装)


	return true;
}
