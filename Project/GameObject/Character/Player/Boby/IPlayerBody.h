#pragma once

#include <list>
#include <memory>

#include "../../../IObject/IObject.h"


// PlayerBodyのタイプ
enum PlayerBodyTyep {
	MAIN,
	LEFT,
	RIGHTM
};


// Player前方宣言
class Player;


/* PlayerBodyの基底クラス */
class IPlayerBody : public IObject {


public:

	// 仮想デストラクタ
	virtual ~IPlayerBody() = default;

};