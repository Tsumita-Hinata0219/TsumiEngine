#include "IEnemyEffect.h"
#include "3D/Model/ModelManager/ModelManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
IEnemyEffect::IEnemyEffect()
{
	// ModelManagerのインスタンスを取得
	modelManager_ = ModelManager::GetInstance();
}
