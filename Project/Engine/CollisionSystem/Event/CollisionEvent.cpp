#include "CollisionEvent.h"



// パラメータ付きコンストラクタ
CollisionEvent::CollisionEvent(CollisionComponent* comp1, CollisionComponent* comp2)
{
	this->component1_ = comp1;
	this->component2_ = comp2;
}
