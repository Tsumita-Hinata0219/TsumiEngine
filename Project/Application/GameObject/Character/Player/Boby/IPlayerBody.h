#pragma once

#include <list>
#include <memory>

#include "../../../IObject/IObject.h"


// PlayerBodyのタイプ
enum class PlayerBodyTyep {
	MAIN,
	LEFT,
	RIGHTM,
	Count,
};

// Player前方宣言
class Player;

/* PlayerBodyの基底クラス */
class IPlayerBody : public IObject {

public:

	// 仮想デストラクタ
	virtual ~IPlayerBody() = default;

	// ペアレントを結ぶ
	virtual void SetParent(Transform* parent) = 0;
};