#include "Model.h"
#include "ModelManager.h"
#include "KeyFrameAnimation.h"



/// <summary>
/// コンストラクタ
/// </summary>
Model::Model() {

	// ModelManagerのインスタンス取得
	modelManager_ = ModelManager::Getinstance();

	// KeyFrameAnimationのインスタンス取得
	keyFrameAnimation_ = KeyFrameAnimation::GetInstance();
}

/// <summary>
/// 初期化処理
/// </summary>
void Model::Initialize(IModelState* state, WorldTransform worldTransform) {

	// ワールド座標のデフォルト設定
	this->worldTransform_ = worldTransform;

	// テクスチャの初期設定
	this->useTexture_ = 1;

	// 色の設定
	this->color_ = Vector4::one;

	// 光の設定
	this->light_.color = Vector4::one;
	this->light_.direction = { 0.0f, -1.0f, 0.0f };
	//this->light_.SpecularFColor = { 1.0f, 1.0f, 1.0f };
	this->light_.intensity = 1.0f;
	this->light_.sininess = 1.0f;
	this->light_.enableLightting = false;

	// モデルの描画タイプ
	this->modelDrawType_ = Phong;

	// ステートパターンの初期化処理
	this->state_ = state;
	this->state_->Initialize(this);
}


/// <summary>
/// Objファイルの読み込み & Obj初期化処理
/// </summary>
void Model::CreateFromObj(const std::string& routeFilePath, const std::string& fileName, WorldTransform worldTransform) {

	// ワールド座標のデフォルト設定
	this->worldTransform_ = worldTransform;

	// テクスチャの初期設定
	this->useTexture_ = 1;

	// 色の設定
	this->color_ = Vector4::one;

	// 光の設定
	this->light_.color = Vector4::one;
	this->light_.direction = { 0.0f, -1.0f, 0.0f };
	//this->light_.SpecularFColor = { 1.0f, 1.0f, 1.0f };
	this->light_.intensity = 1.0f;
	this->light_.sininess = 1.0f;
	this->light_.enableLightting = false;

	// Objファイルパス
	this->fileName_ = fileName;
	this->routeFilePath_ = routeFilePath;

	// Objの読み込み
	this->objData_ = modelManager_->LoadObjFile(routeFilePath, fileName);

	// モデルの描画タイプ
	this->modelDrawType_ = Phong;

	// ステートパターンの初期化処理
	this->state_ = new ModelObjState();
	this->state_->Initialize(this);
}

void Model::CreateFromObjAssimpVer(const std::string& routeFilePath, const std::string& fileName, WorldTransform worldTransform) {

	// ワールド座標のデフォルト設定
	this->worldTransform_ = worldTransform;

	// テクスチャの初期設定
	this->useTexture_ = 1;

	// 色の設定
	this->color_ = Vector4::one;

	// 光の設定
	this->light_.color = Vector4::one;
	this->light_.direction = { 0.0f, -1.0f, 0.0f };
	//this->light_.SpecularFColor = { 1.0f, 1.0f, 1.0f };
	this->light_.intensity = 1.0f;
	this->light_.sininess = 1.0f;
	this->light_.enableLightting = false;

	// Objファイルパス
	this->fileName_ = fileName;
	this->routeFilePath_ = routeFilePath;

	// Objの読み込み
	this->objData_ = modelManager_->LoadObjFileAssimpVer(routeFilePath, fileName);

	// モデルの描画タイプ
	this->modelDrawType_ = Phong;

	// ステートパターンの初期化処理
	this->state_ = new ModelObjState();
	this->state_->Initialize(this);
}

void Model::CreateGLTFModel(const std::string& routeFilePath, const std::string& fileName, const std::string& textureName, WorldTransform worldTransform) {

	// ワールド座標のデフォルト設定
	this->worldTransform_ = worldTransform;

	// テクスチャの初期設定
	this->useTexture_ = 1;

	// 色の設定
	this->color_ = Vector4::one;

	// 光の設定
	this->light_.color = Vector4::one;
	this->light_.direction = { 0.0f, -1.0f, 0.0f };
	//this->light_.SpecularFColor = { 1.0f, 1.0f, 1.0f };
	this->light_.intensity = 1.0f;
	this->light_.sininess = 1.0f;
	this->light_.enableLightting = false;

	// Objファイルパス
	this->fileName_ = fileName;
	this->routeFilePath_ = routeFilePath;

	// Objの読み込み
	this->objData_ = modelManager_->LoadGLTF(routeFilePath, fileName, textureName);

	// モデルの描画タイプ
	this->modelDrawType_ = Phong;

	// ステートパターンの初期化処理
	this->state_ = new ModelGLTFState();
	this->state_->Initialize(this);
}


/// <summary>
/// 描画処理
/// </summary>
void Model::Draw(WorldTransform worldTransform, Camera* camera) {

	this->state_->Draw(this, worldTransform, camera);
}


/// <summary>
/// Animationの再生
/// </summary>
void Model::PlayAnimation(Animation animation, float time)
{
	// GLTFで読み込んだモデルじゃないとダメ
	assert(this->state_->GetStateType() == ModelStateType::gLTF && "その読み込み形式はだめだよ");

	// timeにあったAnimationを解析して、LocalMatrixに入れる
	this->objData_.rootNode.localMatrix = keyFrameAnimation_->PlayAnimation(this->objData_.rootNode.name, animation, time);
}


/// <summary>
/// Nodeの階層構造からSkeletonを作る
/// </summary>
Skeleton Model::CreateSkeleton()
{
	// GLTFで読み込んだモデルじゃないとダメ
	assert(this->state_->GetStateType() == ModelStateType::gLTF && "その読み込み形式はだめだよ");

	return modelManager_->CreateSkeleton(this->objData_.rootNode);
}


/// <summary>
/// Skeletonの更新処理
/// </summary>
void Model::UpdateSkeleton(Skeleton& skeleton)
{
	// すべてのJointを更新。親が若いので通常ループで処理可能になっている
	for (Joint& joint : skeleton.joints) {
		
		joint.localMatrix = MakeAffineMatrix(joint.transform.scale, joint.transform.rotate, joint.transform.translate);

		// 親がいれば親の行列を掛ける
		if (joint.parent) {

			joint.skeletonSpaceMatrix = joint.localMatrix * skeleton.joints[*joint.parent].skeletonSpaceMatrix;
		}
		else { // 親がいないのでlocalMatrixとskeletonSpaceMatrixは一致する

			joint.skeletonSpaceMatrix = joint.localMatrix;
		}
	}
}


/// <summary>
/// Animationを適用する
/// </summary>
void Model::ApplyAnimation(Skeleton& skeleton, const Animation& animation, float animationTime)
{
	keyFrameAnimation_->ApplyAnimation(skeleton, animation, animationTime);
}
