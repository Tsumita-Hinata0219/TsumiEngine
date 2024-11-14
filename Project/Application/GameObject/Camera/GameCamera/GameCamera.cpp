#include "GameCamera.h"
#include "../../Character/Player/Player.h"


/// <summary>
/// 初期化
/// </summary>
void GameCamera::Init()
{
	// Inputクラス
	input_ = Input::GetInstance();

	// カメラマネージャーのインスタンス取得
	cameraManager_ = CameraManager::GetInstance();
	// カメラリソース
	camera_.Init();
	camera_.srt.rotate = { 0.3f, 0.0f, 0.0f };
	cameraManager_->ReSetData(camera_);

	// 相対位置
	constOffset_ = { 0.0f, 20.0f, -50.0f };

	// オフセットの設定
	playerOffset_ = constOffset_;
}


/// <summary>
/// 更新処理
/// </summary>
void GameCamera::Update()
{
	// カメラデータの更新
	camera_.Update();

	// stickの入力を受け取る
	iRStick_ = input_->GetRStick();

	// 回転処理
	FuncOrientation();

	// フォロー処理
	FuncFollow();

	// 前方ベクトルと右方ベクトルを求める
	CalcForwardVec();
	CalcRightVec();

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
/// 回転処理
/// </summary>
void GameCamera::FuncOrientation()
{
	if (std::abs(iRStick_.x) > DZone_ || std::abs(iRStick_.y) > DZone_) {

		// 目標回転角度
		float addAngle = iRStick_.x * addOrientationSpeed_;

		// 現在の角度と目標角度の計算
		float targetAngle = camera_.srt.rotate.y + addAngle;

		// 現在の角度を目標角度の間を補間
		camera_.srt.rotate.y =
			Lerp(camera_.srt.rotate.y, targetAngle, orientationLerpSpeed_);
	}
}


/// <summary>
/// フォロー処理
/// </summary>
void GameCamera::FuncFollow()
{
	// オフセットの設定
	playerOffset_ = constOffset_;

	// カメラの前方方向に基づいてカメラのオフセットを回転させる
	Matrix4x4 rotateMat = Matrix4x4::identity;
	rotateMat = MakeRotateYMatrix(camera_.srt.rotate.y);

	// カメラのオフセットの回転
	playerOffset_ = TransformWithPerspective(playerOffset_, rotateMat);

	// プレイヤーの位置にオフセットを加えてカメラの位置を更新
	camera_.srt.translate = player_->GetWorldPos() + playerOffset_;

	// Yの位置だけ固定
	camera_.srt.translate.y = constOffset_.y;
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
	if (ImGui::TreeNode("FollowCamera")) {

		camera_.DrawImGui();

		ImGui::TreePop();
	}
}
