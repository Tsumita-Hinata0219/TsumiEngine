#include "IEnemyState.h"

// 初期ステート
int IEnemyState::stateNo_ = EnemyState::SPAWN;

// ステート番号の取得
int IEnemyState::GetStateNo() { return stateNo_; }
