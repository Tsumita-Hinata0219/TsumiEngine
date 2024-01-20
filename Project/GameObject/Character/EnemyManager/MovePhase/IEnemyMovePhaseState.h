#pragma once

// 各挙動をenumで定義
enum MovePhase {
	Approach,
	Leave,
};

// Enemyの前方宣言
class Enemy;

/* IEnemyMovePhaseStateクラス */
class IEnemyMovePhaseState {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	IEnemyMovePhaseState() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~IEnemyMovePhaseState() {};


	//　──────── 純粋仮想関数　※派生クラスに実装を強制する ──────── //

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void InitState(Enemy* enemy) = 0;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void UpdateState() = 0;

	/// <summary>
	/// 終了時処理
	/// </summary>
	virtual void ExitState() = 0;

	/// <summary>
	/// フェーズの変更
	/// </summary>
	virtual void ChangeState(int nexrState) = 0;


protected:

	// エネミー
	Enemy* enemy_;
};