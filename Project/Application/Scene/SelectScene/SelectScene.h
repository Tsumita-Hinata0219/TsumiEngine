#pragma once

#include "Scene/IScene.h"
#include "GameManager/GameManager.h"
#include "GameObject/GameObject.h"

#include "GameObject/Others/SceneTransition/SceneTransition.h"

#include "GameObject/Others/StageSelect/Manager/StageSelectManager.h"


/* ステージセレクトシーン */
class SelectScene : public IScene {


public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SelectScene() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SelectScene() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 背景スプライトの描画処理
	/// </summary>
	void BackSpriteDraw() override;

	/// <summary>
	/// ３Dオブジェクトの描画処理
	/// </summary>
	void ModelDraw() override;

	/// <summary>
	/// 前景スプライトの描画処理
	/// </summary>
	void FrontSpriteDraw() override;


private:

	/// <summary>
	/// ゲーム起動してから一度だけ入る初期化
	/// </summary>
	void OnceInit();


private:

	// Input
	Input* input_ = nullptr;

	// カメラ
	CameraManager* cameraManager_ = nullptr;
	std::weak_ptr<CameraData> cameraData_;

	// SceneTransition
	SceneTransition* sceneTransition_ = nullptr;

	// セレクト
	std::unique_ptr<StageSelectManager> selectManager_;

	// 一度訪れたかのフラグ
	bool isVisited_ = false;

	std::unique_ptr<Sprite> sprite_;
	uint32_t texture_;
	Transform trans_{};
};

