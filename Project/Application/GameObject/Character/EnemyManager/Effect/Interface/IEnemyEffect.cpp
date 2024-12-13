#include "IEnemyEffect.h"
#include "3D/Model/Manager/ModelManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
IEnemyEffect::IEnemyEffect()
{
	// ModelManagerのインスタンスを取得
	modelManager_ = ModelManager::GetInstance();
}
