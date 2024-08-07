#pragma once



/* Shapeの抽象基底クラス */
class CollisionShape {

public:

	// 仮想デストラクタ
	virtual ~CollisionShape() = default;

	// 純粋仮想関数 : 異なるシェイプに応じた衝突判定処理
	virtual bool Intersects(const CollisionShape& other) const = 0;
};

