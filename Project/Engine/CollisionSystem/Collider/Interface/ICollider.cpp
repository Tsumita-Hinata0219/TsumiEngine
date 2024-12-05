#include "ICollider.h"
#include "../../Manager/CollisionManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
ICollider::ICollider() 
{
	// マネージャーに自身のポインタを登録
	manager_ = CollisionManager::GetInstance();
	manager_->Register(this);

	// アクティブにする
	isActive_ = true;
}


ICollider::~ICollider() 
{
	// 死ぬときにマネージャーに死んだことを報告し
	// マネージャー側にあるポインタを削除する
	if (manager_ && isActive_) {
		manager_->UnRegister(this);
		isActive_ = false;          // 無効化
	}
}


/// <summary>
/// コライダー無効化
/// </summary>
void ICollider::Deactivate()
{
	// マネージャー側にあるポインタを削除する
	if (manager_ && isActive_) {
		manager_->UnRegister(this); // 登録解除
		isActive_ = false;          // 無効化
	}
}