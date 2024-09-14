#include "FollowCamera.h"
#include "../../Character/Player/Player.h"


// 初期化処理
void FollowCamera::Init()
{
	// Inputクラス
	input_ = Input::GetInstance();

	// モデルのロードと設定
	modelManager_->LoadModel("Obj/FollowCamera", "FollowCamera.obj");
	model_ = modelManager_->GetModel("FollowCamera");

	// Transformの初期化
	trans_.Init();

	// カメラマネージャーのインスタンス取得
	cameraManager_ = CameraManager::GetInstance();
	// カメラリソース
	camera_.Init();
	camera_.srt.rotate = { 0.2f, 0.0f, 0.0f };
	cameraManager_->ReSetData(camera_);

	// 相対位置
	constOffset_ = { 0.0f, 20.0f, -50.0f };

	// オフセットの設定
	playerOffset_ = constOffset_;


}


// 更新処理
void FollowCamera::Update()
{
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


// 描画処理
void FollowCamera::Draw3D()
{
}
void FollowCamera::Draw2DFront()
{
}
void FollowCamera::Draw2DBack()
{
}


// 衝突判定コールバック関数
void FollowCamera::onCollision(IObject* object)
{
}


// 回転処理
void FollowCamera::FuncOrientation()
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


// フォロー処理
void FollowCamera::FuncFollow()
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


// 前方ベクトルを求める
void FollowCamera::CalcForwardVec()
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


// 右方ベクトルを求める
void FollowCamera::CalcRightVec()
{
	// デフォルトの前方ベクトル
	Vector3 deffRightVec = Vector3::oneX;

	// Y軸の回転行列
	Matrix4x4 rotateYMat =
		MakeRotateYMatrix(camera_.srt.rotate.y);

	// 前方ベクトルを求める
	forwardVec_ =
		TransformWithPerspective(deffRightVec, rotateYMat);
}


// ImGuiの描画
void FollowCamera::DrawImGui()
{
	if (ImGui::TreeNode("FollowCamera")) {



		ImGui::TreePop();
	}
}

