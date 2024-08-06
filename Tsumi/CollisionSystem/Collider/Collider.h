#pragma once

#include "../Detector/CollisionDetector.h"

/* 抽象的なコライダークラス */
class Collider {

public:

	// コンストラクタ
	Collider() : id(nextID++) {};

	// 仮想デストラクタ
	virtual ~Collider() = default;

	// 更新処理
	virtual void Update() = 0;

	// 衝突判定処理
	virtual bool Detext(const Collider& other) const = 0;


protected:

	// コライダーの持つID
	int id;
	static int nextID;
};