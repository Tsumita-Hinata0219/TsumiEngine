#include "TestHuman.h"



// 初期化処理
void TestHuman::Init()
{
	testModel_ = make_unique<Model>();
	testModel_->CreateGLTFModel("TestHuman", "walk", "uvChecker.png");
	testAnimation_ = AnimationManager::LoadAnimationFile("TestHuman", "walk");
	skeleton_ = testModel_->CreateSkeleton();
	skinCluster_ = testModel_->CreateSkinCluster(skeleton_);

	wt_.Initialize();
}


// 更新処理
void TestHuman::Update()
{
	wt_.UpdateMatrix();

	// アニメーションの時間を進める
	animationtime += 1.0f / 60.0f;
	if (animationtime >= 1.0f) {
		animationtime = 0.0f;
	}

	// アニメーションの更新を行って、骨ごとのLocal情報を更新する
	testModel_->ApplyAnimation(skeleton_, testAnimation_, animationtime);

	// 現在の骨ごとのLocal情報を基にSKeletonSpaceの情報を更新する
	testModel_->UpdateSkeleton(skeleton_);

	// SkeletonSpaceの情報を基にSkinClusterのMatrixPaletteを更新する
	testModel_->UpdateSkinCluster(skinCluster_, skeleton_);

#ifdef _DEBUG

	if (ImGui::TreeNode("TestHuman")) {

		ImGui::DragFloat3("Scale", &wt_.srt.scale.x, 0.1f);
		ImGui::DragFloat3("Rotate", &wt_.srt.rotate.x, 0.1f);
		ImGui::DragFloat3("Translate", &wt_.srt.translate.x, 0.1f);

		ImGui::Text("");
		ImGui::DragFloat("Animationtime", &animationtime, 0.01f, 0.0f, 10.f);

		ImGui::TreePop();
	}

#endif // _DEBUG
}


// 描画処理
void TestHuman::Draw(Camera* camera)
{
	//testModel_->Draw(wt_, camera);
	testModel_->AnimDraw(wt_, skinCluster_, camera);
}
