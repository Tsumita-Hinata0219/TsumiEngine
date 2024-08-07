#pragma once

#include "../Event/CollisionEvent.h"

/* コリジョンイベントのリスナーを追加するクラス */
class CollisionListener {

public:

	// 仮想デストラクタ
	virtual ~CollisionListener() = default;

	// 純粋仮想関数 : コリジョンイベントを処理するためのクラス
	virtual void OnCollision(const CollisionEvent& event) = 0;
};

