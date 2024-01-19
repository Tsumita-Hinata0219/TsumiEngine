#include "DebugCamera.h"



/// <summary>
/// インスタンスの取得
/// </summary>
DebugCamera* DebugCamera::GetInstance() {
	static DebugCamera instance;
	return &instance;
}


/// <summary>
/// 初期化処理
/// </summary>
void DebugCamera::Initialize() {

	DebugCamera::GetInstance()->DebugViewProjection_.Initialize();
	DebugCamera::GetInstance()->matRotate_ = Matrix4x4::identity;
	DebugCamera::GetInstance()->worldTransform_.Initialize();
}


/// <summary>
/// 更新処理
/// </summary>
void DebugCamera::Update() {

	DebugCamera::GetInstance()->worldTransform_.UpdateMatrix();
	DebugCamera::GetInstance()->DebugViewProjection_.UpdateMatrix();


	// 中心からずらす
	Vector3 offset = DebugCamera::GetInstance()->offset_;
	offset = TransformNormal(offset, DebugCamera::GetInstance()->matRotate_);
	DebugCamera::GetInstance()->worldTransform_.translate = offset;


	// Translateの更新
	Matrix4x4 translateMat = MakeTranslateMatrix(
		DebugCamera::GetInstance()->worldTransform_.translate);

	// worldTransformの更新
	DebugCamera::GetInstance()->worldTransform_.matWorld =
		DebugCamera::GetInstance()->matRotate_ * translateMat;

	// view行列の更新
	DebugCamera::GetInstance()->DebugViewProjection_.matView =
		Inverse(translateMat) * Inverse(DebugCamera::GetInstance()->matRotate_);


	ImGui::Begin("DebugCamera");
	ImGui::Checkbox("isDebugCamera", &DebugCamera::GetInstance()->isDebugCamera_);
	ImGui::DragFloat3("Rotate", &DebugCamera::GetInstance()->worldTransform_.rotate.x, 0.01f);
	ImGui::DragFloat3("translate", &DebugCamera::GetInstance()->worldTransform_.translate.x, 0.1f);
	ImGui::End();
}


/// <summary>
/// 描画処理
/// </summary>
void DebugCamera::Draw() {


}