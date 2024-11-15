#pragma once


// GameCameraの前方宣言
class GameCamera;

/* IPlayerMovementの基底クラス
   移動処理のステートパターン */
class ICameraControlStateh {

public:

	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~ICameraControlStateh() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Enter(GameCamera* pCamera) = 0;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() = 0;


protected:

	GameCamera* gameCamera_ = nullptr;

};



