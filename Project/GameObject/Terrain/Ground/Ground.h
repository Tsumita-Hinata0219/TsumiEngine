#pragma once

#include "GameObject.h"


/* Groundクラス */
class Ground : public OBBCollider {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Ground() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Ground() {};

	/// <summary>
	/// インスタンスの取得
	/// </summary>
	static Ground* GetInstance();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ViewProjection view);

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	void OnCollision(ObjectBit id) override;


#pragma region Get

	// ワールド座標の取得
	Vector3 GetWorldPosition() override { return this->worldTransform_.GetWorldPos(); }

	// Rotateの取得
	Vector3 GetRotate() override { return this->worldTransform_.rotate; }

	// Sizeの取得
	Vector3 GetSize() override { return this->size_; }

#pragma endregion 


private:

	// OBBの設定
	void SettingOBBProperties();


private:

	// モデル
	std::unique_ptr<Model> model_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform worldTransform_{};

	// サイズ
	Vector3 size_{};

};

