#pragma once

#include <list>
#include <memory>

#include "../../IObject/IObject.h"
#include "../../GameObject.h"


// 前方宣言
class Player;


/* フォローカメラクラス */
class FollowCamera : public IObject {

public: // メンバ関数

	// コンストラクタ、デストラクタ
	FollowCamera() = default;
	~FollowCamera() = default;

	// 初期化処理　更新処理　描画処理
	void Init() override;
	void Update() override;
	void Draw3D() override;
	void Draw2DFront() override;
	void Draw2DBack() override;

	// 衝突判定コールバック関数
	void onCollision([[maybe_unused]] IObject* object) override;


#pragma region Accessor アクセッサ

	// Player
	void SetPlayer(Player* player) { this->player_ = player; }

	// ForwardVec
	Vector3& GetForwardVec() { return this->forwardVec_; }

	// RightVec
	Vector3& GetRightVec() { return this->rightVec_; }

#pragma endregion 


private:

	// 回転処理
	void FuncOrientation();

	// フォロー処理
	void FuncFollow();

	// 前方ベクトルを求める
	void CalcForwardVec();

	// 右方ベクトルを求める
	void CalcRightVec();

	// ImGuiの描画
	void DrawImGui();


private:

	// プレイヤー
	Player* player_ = nullptr;

	// カメラマネージャー
	CameraManager* cameraManager_ = nullptr;
	// カメラ本体
	CameraResource camera_{};

	// 入力
	TsumiEngine::Input* input_ = nullptr;
	// LStickの入力
	Vector2 iRStick_{};
	// デッドゾーン
	const float DZone_ = 0.2f;

	// 回転速度
	float addOrientationSpeed_ = 0.15f;
	// 姿勢計算の補間速度
	float orientationLerpSpeed_ = 0.5f;

	// 相対位置
	Vector3 constOffset_{};
	// プレイヤーからのオフセット
	Vector3 playerOffset_{};

	// 前方ベクトル
	Vector3 forwardVec_{};
	// 右方ベクトル
	Vector3 rightVec_{};


};

