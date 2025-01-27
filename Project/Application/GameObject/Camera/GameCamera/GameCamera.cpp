#include "GameCamera.h"
#include "../../Character/Player/Player.h"


/// <summary>
/// 初期化
/// </summary>
void GameCamera::Init()
{
	// カメラマネージャーのインスタンス取得
	cameraManager_ = CameraManager::GetInstance();
	// カメラリソース
	camera_.Init();
	cameraManager_->ReSetData(camera_);

	// 操作処理クラス
	control_ = std::make_unique<GameCameraControl>();
	control_->Init(this, player_, &camera_);
}


/// <summary>
/// 更新処理
/// </summary>
void GameCamera::Update()
{
	// カメラデータの更新
	camera_.Update();

	// 操作処理
	control_->Update();

	// 前方ベクトルと右方ベクトルを求める
	CalcForwardVec();
	CalcRightVec();

	// シェイク中
	if (isShake_) {
		ExecuteShake();
	}

#ifdef _DEBUG
	// ImGuiの描画
	DrawImGui();
#endif // _DEBUG
}


/// <summary>
/// 描画処理
/// </summary>
void GameCamera::Draw3D()
{
}
void GameCamera::Draw2DFront()
{
}
void GameCamera::Draw2DBack()
{
}

/// <summary>
/// 衝突判定コールバック関数
/// </summary>
void GameCamera::onCollision([[maybe_unused]] IObject * object)
{
}


/// <summary>
/// カメラのシェイク開始
/// </summary>
void GameCamera::ActivateShake()
{

}


/// <summary>
/// 前方ベクトルを求める
/// </summary>
void GameCamera::CalcForwardVec()
{
	// デフォルトの前方ベクトル
	Vector3 deffForwardVec = Vector3::oneZ;

	// Y軸の回転行列
	Matrix4x4 rotateYMat =
		MakeRotateYMatrix(camera_.srt.rotate.y);

	// 前方ベクトルを求める
	forwardVec_ =
		TransformWithPerspective(deffForwardVec, rotateYMat);
}


/// <summary>
/// 右方ベクトルを求める
/// </summary>
void GameCamera::CalcRightVec()
{
	// デフォルトの前方ベクトル
	Vector3 deffRightVec = Vector3::oneX;

	// Y軸の回転行列
	Matrix4x4 rotateYMat =
		MakeRotateYMatrix(camera_.srt.rotate.y);

	// 前方ベクトルを求める
	rightVec_ =
		TransformWithPerspective(deffRightVec, rotateYMat);
}


/// <summary>
/// ImGuiの描画
/// </summary>
void GameCamera::DrawImGui()
{
	if (ImGui::TreeNode("GameCamera")) {

		camera_.DrawImGui();

		ImGui::TreePop();
	}
}


/// <summary>
/// シェイク処理
/// </summary>
void GameCamera::ExecuteShake()
{
}
