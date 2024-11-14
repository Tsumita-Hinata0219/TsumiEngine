#pragma once


// Playerの前方宣言
class Player;

/* IPlayerMovementの基底クラス
   移動処理のステートパターン */
class IPlayerMovement {

public:

	// 仮想デストラクタ
	virtual ~IPlayerMovement() = default;

	// 初期化、更新
	virtual void Eneter() = 0;
	virtual void Update() = 0;


};

