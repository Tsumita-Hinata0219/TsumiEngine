#pragma once

#include "../IEnemyShotPattern.h"

/* 射撃タイプ : ランダム */
class EnemyShotPatternRandom : public IEnemyShotPattern {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyShotPatternRandom() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyShotPatternRandom() = default;

	/// <summary>
	/// 射撃処理
	/// </summary>
	void Execute() override;


private:


};
