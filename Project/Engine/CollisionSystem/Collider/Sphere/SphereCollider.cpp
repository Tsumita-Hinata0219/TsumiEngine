#include "SphereCollider.h"
#include "GameObject/IObject/IObject.h"


/// <summary>
/// パラメータ付きコンストラクタ
/// </summary>
Collider::SphereCollider::SphereCollider(IObject* setOwner)
{
	// オーナーと属性の設定
	this->owner_ = setOwner;
	this->attribute_ = int(this->owner_->GetAttribute());
}
