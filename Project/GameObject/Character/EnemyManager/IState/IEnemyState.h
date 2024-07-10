#pragma once


// ステートの種類
namespace EnemyState {

	enum EnemyState {
		SPAWN,
		APPROACH,
		DEATH,
	};
}

/* IEnemyState基底クラス */
class IEnemyState {

public:

	// コンストラクタ、デストラクタ
	~IEnemyState() {};

	// 初期化、更新、終了
	virtual void InitState() = 0;
	virtual void UpdateState() = 0;
	virtual void ExitState() = 0;

	// ステート変更
	virtual void ChangeState(int nextState) = 0;

#pragma region Accessor

	// ステート番号の取得
	int GetStateNo();

#pragma endregion 

protected:

	static int stateNo_;
};


