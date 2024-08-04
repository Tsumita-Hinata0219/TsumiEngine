#pragma once



/* 衝突判定の基本インターフェイス */
class CollisionDetector {

public:

	// 仮想デストラクタ
	virtual ~CollisionDetector() = default;

	// 純粋仮想関数 : 派生クラスで具体的な衝突判定ロジックを実装するための関数
	virtual bool Detect() = 0;
};

