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
}

/// <summary>
/// 仮想デストラク
/// </summary>
ICollider::~ICollider() 
{
	// 死ぬときにマネージャーに死んだことを報告し
	// マネージャー側にあるポインタを削除する
	if (manager_) {
		manager_->UnRegister(this);
	}
}