#include "Transform.h"



// 初期化処理
void Transform::Initialize()
{
	matWorld = Matrix4x4::identity;
	UpdateMatrix();
}


// 行列の更新処理
void Transform::UpdateMatrix()
{
	// スケール、回転、並列移動を合成して行列を計算する
	matWorld = MakeAffineMatrix(srt.scale, srt.rotate, srt.translate);

	// 親があれば親のワールド行列を掛ける
	if (parent) {
		matWorld *= parent->matWorld;
	}
}


// モデルの読み込み
void Transform::DrawImGui(std::string label)
{
	ImGui::DragFloat3((label + "_Scale").c_str(), &srt.scale.x, 0.1f);
	ImGui::DragFloat3((label + "_Rotate").c_str(), &srt.rotate.x, 0.1f);
	ImGui::DragFloat3((label + "_Translate").c_str(), &srt.translate.x, 0.1f);
}


// ワールド座標の取得
Vector3 Transform::GetWorldPos()
{
	return { matWorld.m[3][0], matWorld.m[3][1], matWorld.m[3][2] };
}


// 親子関係を結ぶ
void Transform::SetParent(const Transform* parentTransform)
{
	parent = parentTransform;
}
