#include "Model.h"
#include "ModelManager/ModelManager.h"
#include "../../Animation/KeyFrameAnimation/KeyFrameAnimation.h"


/// <summary>
/// コンストラクタ
/// </summary>
Model::Model()	
{
	// ModelManagerのインスタンス取得
	modelManager_ = ModelManager::Getinstance();

	// KeyFrameAnimationのインスタンス取得
	keyFrameAnimation_ = KeyFrameAnimation::GetInstance();

	// CameraManagerのインスタンスの取得
	cameraManager_ = CameraManager::GetInstance();
}
Model::Model(ModelDatas datas) : datas_(datas)
{
	// ModelManagerのインスタンス取得
	modelManager_ = ModelManager::Getinstance();

	// KeyFrameAnimationのインスタンス取得
	keyFrameAnimation_ = KeyFrameAnimation::GetInstance();

	// CameraManagerのインスタンスの取得
	cameraManager_ = CameraManager::GetInstance();

	// Datasを基にBufferを作成する
	CreateBufferResource();
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
void Model::Draw(WorldTransform worldTransform, Camera* camera) 
{
	this->state_->Draw(this, worldTransform, camera);
}
void Model::AnimDraw(WorldTransform worldTransform, SkinCluster skinCluster, Camera* camera)
{
	this->state_->AnimDraw(this, worldTransform, skinCluster, camera);
}
void Model::DrawN(Transform transform)
{
	// カメラリソースの取得
	cameraResource_ = (*cameraManager_->GetResource());

	// 諸々の計算
	transform.UpdateMatrix();
	transform.transformationMatData.World = transform.matWorld;
	transform.transformationMatData.WVP = transform.transformationMatData.World * cameraResource_.viewMatrix * cameraResource_.projectionMatrix;
	transform.transformationMatData.WorldInverseTranspose = Transpose(Inverse(transform.matWorld));

	// ここで書き込み
	// Camera
	cameraManager_->WrirwData();
	// VBV
	buffers_.vertex.Map();
	buffers_.vertex.WriteData(datas_.mesh.vertices.data());
	buffers_.vertex.UnMap();
	// IBV
	buffers_.indeces.Map();
	buffers_.indeces.WriteData(datas_.mesh.indices.data());
	buffers_.indeces.UnMap();
	// Material
	buffers_.material.Map();
	buffers_.material.WriteData(&datas_.material);
	buffers_.material.UnMap();
	// Transform
	buffers_.transform.Map();
	buffers_.transform.WriteData((&transform.transformationMatData));
	buffers_.transform.UnMap();
	// Light
	buffers_.light.Map();
	buffers_.light.WriteData(&datas_.light);
	buffers_.light.UnMap();
	// Environment
	buffers_.enviroment.Map();
	buffers_.enviroment.WriteData(&datas_.environment);
	buffers_.enviroment.UnMap();
	// コマンドコール
	CommandCall();
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


/// <summary>
/// SKinClusterの生成
/// </summary>
SkinCluster Model::CreateSkinCluster(const Skeleton& skeleton)
{
	// 作成するSkinCluster
	SkinCluster result{};

	// palette用のResourceを確保
	result.paletteResource = CreateResource::CreateBufferResource(sizeof(WellForGPU) * skeleton.joints.size());
	WellForGPU* mappedPalette = nullptr;
	result.paletteResource->Map(0, nullptr, reinterpret_cast<void**>(&mappedPalette));
	result.mappedPallette = { mappedPalette, skeleton.joints.size() }; // spanを使ってアクセスするようにする
	result.srvHandle = SRVManager::CreateSkinClusterSRV(result.paletteResource, skeleton); // SRVHandleの設定

	// influence用のResourceを確保
	result.influenceResource = CreateResource::CreateBufferResource(sizeof(VertexInfluence) * this->objData_.vertices.size());
	VertexInfluence* mappedInfluence = nullptr;
	result.influenceResource->Map(0, nullptr, reinterpret_cast<void**>(&mappedInfluence));
	std::memset(mappedInfluence, 0, sizeof(VertexInfluence) * this->objData_.vertices.size()); // 0埋め。weightを0にしておく
	result.mappedInfluence = { mappedInfluence, this->objData_.vertices.size() };

	// influence用のVBVを作成
	result.influenceBufferView.BufferLocation = result.influenceResource->GetGPUVirtualAddress();
	result.influenceBufferView.SizeInBytes = UINT(sizeof(VertexInfluence) * this->objData_.vertices.size());
	result.influenceBufferView.StrideInBytes = sizeof(VertexInfluence);

	// InverseBindPoseMatrixの保存領域を作成。単位行列で埋める
	result.inverseBindPosematrices.resize(skeleton.joints.size());
	std::generate(result.inverseBindPosematrices.begin(), result.inverseBindPosematrices.end(), []() { return Matrix4x4::identity; });

	// ModelDataのSkinCluster情報を解析してInfluenceの中身を埋める
	for (const auto& jointWeight : this->objData_.skinClusterData) { // ModelのSkinClusterの情報を解析
		auto it = skeleton.jointMap.find(jointWeight.first); // jointWeight.firstはjoint名なので、skeletonに対象となるjointが含まれているか判断
		if (it == skeleton.jointMap.end()) { // そんな名前のjointは存在しない。なので次に回す
			continue;
		}

		// (*it).secondにはjointのindexが入っているので、該当indexのinverseBindPoseMatrixを代入
		result.inverseBindPosematrices[(*it).second] = jointWeight.second.inverseBindPoseMatrix;
		for (const auto& vertexWeight : jointWeight.second.vertexWeights) {
			auto& currentInfluence = result.mappedInfluence[vertexWeight.vertexIndex]; // 該当vertexIndexのinfluence情報を参照しておく
			for (uint32_t index = 0; index < kNumMaxInfluence; ++index) { // 空いているところに入れる
				if (currentInfluence.weights[index] == 0.0f) { // weight == 0 が開いている状態なので、その場所にweightとjointのindexを代入
					currentInfluence.weights[index] = vertexWeight.weight;
					currentInfluence.jointIndices[index] = (*it).second;
					break;
				}
			}
		}
	}

	return result;
}


/// <summary>
/// SkinCLusterの更新処理
/// </summary>
void Model::UpdateSkinCluster(SkinCluster& skinCluster, const Skeleton& skeleton)
{
	for (size_t jointIndex = 0; jointIndex < skeleton.joints.size(); ++jointIndex) {

		assert(jointIndex < skinCluster.inverseBindPosematrices.size());

		skinCluster.mappedPallette[jointIndex].skeletonSpaceMatrix =
			skinCluster.inverseBindPosematrices[jointIndex] * skeleton.joints[jointIndex].skeletonSpaceMatrix;

		skinCluster.mappedPallette[jointIndex].skeletonSpaceInverseTransposeMatrix =
			Transpose(Inverse(skinCluster.mappedPallette[jointIndex].skeletonSpaceMatrix));
	}
}



/// <summary>
/// BufferResourceの生成
/// </summary>
void Model::CreateBufferResource()
{
	// mesh
	buffers_.mesh.CreateResource(UINT(datas_.mesh.vertices.size()));
	// vertexBufferView
	buffers_.vertex.CreateResource(UINT(datas_.mesh.vertices.size()));
	buffers_.vertex.CreateVertexBufferView();
	// indexBufferView
	buffers_.indeces.CreateResource(UINT(datas_.mesh.indices.size()));
	buffers_.indeces.CreateIndexBufferView();
	// material
	buffers_.material.CreateResource();
	// transform
	buffers_.transform.CreateResource();
	// light
	buffers_.light.CreateResource();
	// Encironment
	buffers_.enviroment.CreateResource();
}


/// <summary>
/// コマンドコール
/// </summary>
void Model::CommandCall()
{
	// Commandの取得
	Commands commands = CommandManager::GetInstance()->GetCommands();

	// PipeLineCheck
	PipeLineManager::PipeLineCheckAndSet(PipeLineType::Object3D);

	// VertexBufferView
	buffers_.vertex.IASetVertexBuffers(1);
	// IndexBufferView
	buffers_.indeces.IASetIndexBuffer();
	// Material
	buffers_.material.CommandCall(0);
	// TransformationMatrix
	buffers_.transform.CommandCall(1);
	// Camera
	cameraManager_->CommandCall(2);
	// MaterialTexture
	SRVManager::SetGraphicsRootDescriptorTable(3, datas_.material.textureHandle);
	// Light
	buffers_.light.CommandCall(4);
	// Environment
	buffers_.enviroment.CommandCall(5);
	// EnvironmentTexture
	SRVManager::SetGraphicsRootDescriptorTable(6, datas_.environment.textureHandle);
	// Draw!!
	commands.List->DrawIndexedInstanced(UINT(datas_.mesh.indices.size()), 1, 0, 0, 0);
}
