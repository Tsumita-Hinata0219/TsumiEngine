#include "TestHuman.h"



// 初期化処理
void TestHuman::Init()
{
	// Human
	humanModel_ = make_unique<Model>();
	humanModel_->CreateGLTFModel("TestHuman", "walk", "uvChecker.png");
	walkAnim_ = AnimationManager::LoadAnimationFile("TestHuman", "walk");

	humanSkeleton_ = humanModel_->CreateSkeleton();
	humanSkinCluster_ = humanModel_->CreateSkinCluster(humanSkeleton_);

	humanWt_.Initialize();
	humanWt_.srt.translate.x = 2.0f;


	// SimpleSkin
	simpleModel_ = make_unique<Model>();
	simpleModel_->CreateGLTFModel("TestSimpleSkin", "simpleSkin", "simpleSkin.png");
	simpleAnim_ = AnimationManager::LoadAnimationFile("TestSimpleSkin", "simpleSkin");

	simpleSkeleton_ = simpleModel_->CreateSkeleton();
	simpleSkinCluster_ = simpleModel_->CreateSkinCluster(simpleSkeleton_);

	simpleWt_.Initialize();
	simpleWt_.srt.translate.x = -2.0f;

}


// 更新処理
void TestHuman::Update()
{
	// Human
	humanWt_.UpdateMatrix();

	// アニメーションの時間を進める
	animTimeA_ += 1.0f / 60.0f;
	if (animTimeA_ >= 1.0f) {
		animTimeA_ = 0.0f;
	}
	// アニメーションの更新を行って、骨ごとのLocal情報を更新する
	humanModel_->ApplyAnimation(humanSkeleton_, walkAnim_, animTimeA_);
	// 現在の骨ごとのLocal情報を基にSKeletonSpaceの情報を更新する
	humanModel_->UpdateSkeleton(humanSkeleton_);
	// SkeletonSpaceの情報を基にSkinClusterのMatrixPaletteを更新する
	humanModel_->UpdateSkinCluster(humanSkinCluster_, humanSkeleton_);


	// SimpleSkin
	simpleWt_.UpdateMatrix();

	// アニメーションの時間を進める
	animTimeB_ += 0.5f / 60.0f;
	if (animTimeB_ >= 6.0f) {
		animTimeB_ = 0.0f;
	}
	// アニメーションの更新を行って、骨ごとのLocal情報を更新する
	simpleModel_->ApplyAnimation(simpleSkeleton_, simpleAnim_, animTimeB_);
	// 現在の骨ごとのLocal情報を基にSKeletonSpaceの情報を更新する
	simpleModel_->UpdateSkeleton(simpleSkeleton_);
	// SkeletonSpaceの情報を基にSkinClusterのMatrixPaletteを更新する
	simpleModel_->UpdateSkinCluster(simpleSkinCluster_, simpleSkeleton_);

#ifdef _DEBUG

	if (ImGui::TreeNode("TestHuman")) {

		ImGui::DragFloat3("Human_Scale", &humanWt_.srt.scale.x, 0.1f);
		ImGui::DragFloat3("Human_Rotate", &humanWt_.srt.rotate.x, 0.1f);
		ImGui::DragFloat3("Human_Translate", &humanWt_.srt.translate.x, 0.1f);

		ImGui::DragFloat3("Simple_Scale", &simpleWt_.srt.scale.x, 0.1f);
		ImGui::DragFloat3("Simple_Rotate", &simpleWt_.srt.rotate.x, 0.1f);
		ImGui::DragFloat3("Simple_Translate", &simpleWt_.srt.translate.x, 0.1f);

		ImGui::Text("");
		ImGui::DragFloat("Animationtime_A", &animTimeA_, 0.01f, 0.0f, 10.f);
		ImGui::DragFloat("Animationtime_B", &animTimeB_, 0.01f, 0.0f, 10.f);

		ImGui::TreePop();
	}

#endif // _DEBUG
}


// 描画処理
void TestHuman::Draw(Camera* camera)
{
	camera;
	// Human
	humanModel_->AnimDraw(humanWt_, humanSkinCluster_, camera);

	// SimpleSkin
	//simpleModel_->AnimDraw(simpleWt_, simpleSkinCluster_, camera);
}
