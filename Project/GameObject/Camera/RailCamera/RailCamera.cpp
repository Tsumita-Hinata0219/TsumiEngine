#include "RailCamera.h"



// 初期化処理
void RailCamera::Initialize(Vector3 rotate, Vector3 translate)
{
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.rotate = rotate;
	worldTransform_.translate = translate;

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
	//viewProjection_.farZ = 1200.0f;
}


// 更新処理
void RailCamera::Update()
{
	viewProjection_.rotate = worldTransform_.rotate;
	viewProjection_.translate = worldTransform_.translate;
	viewProjection_.matView = Inverse(worldTransform_.matWorld);

	// ワールド座標の更新
	worldTransform_.UpdateMatrix();

	// ビューの更新
	viewProjection_.UpdateMatrix();

#ifdef _DEBUG

	if (ImGui::TreeNode("RailCamera"))
	{
		ImGui::DragFloat3("Rotate", &worldTransform_.rotate.x, 0.01f);
		ImGui::DragFloat3("Translate", &worldTransform_.translate.x, 0.01f);
		ImGui::TreePop();
	}

#endif // _DEBUG
}
