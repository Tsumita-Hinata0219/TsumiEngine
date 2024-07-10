#pragma once


// ステートの種類
enum EnemyState {
	SPAWN,
	APPROACH,
	DEATH,
	Count,
};

/* IEnemyState基底クラス */
class IEnemyState {

public:

	// 仮想デストラクタ
	virtual ~IEnemyState() = default;

	// 初期化、更新、終了
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Exit() = 0;

#pragma region Accessor

	// ステート番号の取得
	int GetStateNo();

#pragma endregion 


public:

	static int stateNo_;
};


