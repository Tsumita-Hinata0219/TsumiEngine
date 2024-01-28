#pragma once

#include "GameObject.h"

#include "Player/Bullet/PlayerBullet.h"
#include "Player/Reticle/PlayerReticle.h"


// GameSceneの前方宣言
class GameScene;

/* Playerクラス */
class Player : public OBBCollider {

public: // プレイヤー本体 : メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(Vector3 initTranslate);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(ViewProjection view);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw3D(ViewProjection view);
	void Draw2DFront(ViewProjection view);

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	void OnCollision(uint32_t id) override;


#pragma region Get

	/// <summary>
	/// ワールドトランスフォームの取得
	/// </summary>
	WorldTransform GetWorldTransform() { return this->worldTransform_; }

	/// <summary>
	/// ワールド座標の取得
	/// </summary>
	Vector3 GetWorldPosition() override { return this->worldTransform_.GetWorldPos(); }

	/// <summary>
	/// 回転軸の取得
	/// </summary>
	Vector3 GetRotate() override { return this->worldTransform_.rotate; }

	/// <summary>
	/// サイズの取得
	/// </summary>
	Vector3 GetSize() override { return this->size_; }

#pragma endregion

#pragma region Set

	/// <summary>
	/// GameSceneの設定
	/// </summary>
	void SetRegisterScene(GameScene* scene) { GameScene_ = scene; }

	/// <summary>
	/// ペアレントの設定
	/// </summary>
	void SetParent(WorldTransform* parent) { worldTransform_.SetParent(parent); }

#pragma endregion

private: // プレイヤー本体 : メンバ関数

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// 射撃処理
	/// </summary>
	void Attack();

	/// <summary>
	/// OBBの設定
	/// </summary>
	void SettingOBBProperties();

private: // プレイヤー本体 : メンバ変数

	// モデル
	std::unique_ptr<Model> model_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform worldTransform_{};

	// 加算速度
	Vector3 velocity_{};

	// 移動量
	Vector3 move_{};
	float moveSpeed_;

	// 移動限界
	const VHInfo vhInfo = { 12.5f, 1.5f, 14.5f, -14.5f };

	// サイズ
	Vector3 size_{};


private: // プレイヤーバレット : メンバ関数

	/// <summary>
	/// バレットリストの登録
	/// </summary>
	void PushBackBulletList();

	/// <summary>
	/// バレットの進行方向の計算
	/// </summary>
	Vector3 CalcDirection();

private: // プレイヤーバレット : メンバ変数

	// 登録先シーン
	GameScene* GameScene_ = nullptr;

	// モデル
	std::unique_ptr<Model> modelBullet_ = nullptr;

	// 移動速度
	const float kBulletSpeed_ = 4.0f;


private: // プレイヤーのレティクル : メンバ関数

	/// <summary>
	/// レティクルの更新処理
	/// </summary>
	void ReticleUpdate(ViewProjection view);


private: // プレイヤーのレティクル : メンバ変数

	// レティクル
	std::unique_ptr<PlayerReticle> reticle_ = nullptr;

};

