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
}
Model::Model(ModelDatas datas) : datas_(datas)
{
	// ModelManagerのインスタンス取得
	modelManager_ = ModelManager::Getinstance();

	// KeyFrameAnimationのインスタンス取得
	keyFrameAnimation_ = KeyFrameAnimation::GetInstance();

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
/// モデルの読み込み
/// </summary>
unique_ptr<Model> Model::LoadObjFileAssimpVer(const std::string& routeFilePath, const std::string& fileName)
{
	/* 1. 中で必要となる変数の宣言 */
	// return するModelに名前を付けておく。(ファイル名)
	auto result = make_unique<Model>();
	result->datas_.name_ = fileName.substr(0, fileName.size() - 4);
	result->datas_.fileFormat_ = GetExtension(fileName);


	/* 2. ファイルを開く */
	// asssimpでobjを読む
	Assimp::Importer importer;
	string file = ("Resources/Obj/" + routeFilePath + "/" + fileName);


	/* 3. 実際にファイルを読み、ModelDataを構築していく */
	//三角形の並び順を逆にする。UVをフリップする(texcoord.y = 1.0f - texcoord.y;の処理)
	const aiScene* scene = importer.ReadFile(file.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs);
	assert(scene->HasMeshes()); // メッシュがないのは対応しない


	// mesh & indicesを解析する
	result->ParseMeshData(scene);

	// materialを解析する
	result->ParseMaterialData(scene, routeFilePath);

	// lightの作成

	// 作ったデータを基にbufferを作っていく
	result->CreateBufferResource();


	return result;
}
unique_ptr<Model> Model::LoadGLTF(const std::string& routeFilePath, const std::string& fileName)
{
	/* 1. 中で必要となる変数の宣言 */
	// return するModelに名前を付けておく。(ファイル名)
	auto result = make_unique<Model>();
	result->datas_.name_ = fileName.substr(0, fileName.size() - 4);
	result->datas_.fileFormat_ = GetExtension(fileName);


	/* 2. ファイルを開く */
	// asssimpでobjを読む
	Assimp::Importer importer;
	string file = ("Resources/gLTF/" + routeFilePath + "/" + fileName);


	/* 3. 実際にファイルを読み、ModelDataを構築していく */
	//三角形の並び順を逆にする         UVをフリップする(texcoord.y = 1.0f - texcoord.y;の処理)
	const aiScene* scene = importer.ReadFile(file.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs);
	assert(scene->HasMeshes()); // メッシュがないのは対応しない


	// mesh & indicesを作成 & 解析
	result->ParseMeshData(scene);

	// materialを作成 & 解析
	result->ParseMaterialData(scene, routeFilePath);

	// lightの作成

	// 作ったデータを基にbufferを作っていく
	result->CreateBufferResource();


	return result;
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
void Model::DrawN(Transform transform, Camera* camera)
{
	// 諸々の計算
	transform.UpdateMatrix();
	transform.transformationMatData.World = transform.matWorld;
	transform.transformationMatData.WVP = transform.transformationMatData.World * camera->viewMatrix * camera->projectionMatrix;
	transform.transformationMatData.WorldInverseTranspose = Transpose(Inverse(transform.matWorld));

	// ここで書き込み
	// VBV
	buffers_.vertexBuffer_.Map();
	buffers_.vertexBuffer_.WriteData(datas_.meshData_.vertices.data());
	buffers_.vertexBuffer_.UnMap();
	// IBV
	buffers_.indecesBuffer_.Map();
	buffers_.indecesBuffer_.WriteData(datas_.meshData_.indices.data());
	buffers_.indecesBuffer_.UnMap();
	// Material
	buffers_.materialBuffer_.Map();
	buffers_.materialBuffer_.WriteData(&datas_.materialData_);
	buffers_.materialBuffer_.UnMap();
	// Transform
	buffers_.transformBuffer_.Map();
	buffers_.transformBuffer_.WriteData((&transform.transformationMatData));
	buffers_.transformBuffer_.UnMap();
	// Light
	buffers_.lightBuffer_.Map();
	buffers_.lightBuffer_.WriteData(&datas_.lightData_);
	buffers_.lightBuffer_.UnMap();

	// コマンドコール
	CommandCall(camera);
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
/// Indicesの解析
/// </summary>
void Model::ParseMeshData(const aiScene* scene)
{
	// mesh & indicesを解析する
	// 今回作るmesh & indeces
	for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex) {
		aiMesh* mesh = scene->mMeshes[meshIndex];
		assert(mesh->HasNormals()); // 法線がないMeshは小名木は非対応
		assert(mesh->HasTextureCoords(0)); // TexcoordがないMeshは今回は非対応
		datas_.meshData_.vertices.resize(mesh->mNumVertices); // 最初に頂点数分のメモリを確保しておく

		// Verticesを解析する
		for (uint32_t vertexIndex = 0; vertexIndex < mesh->mNumVertices; ++vertexIndex) {
			aiVector3D& position = mesh->mVertices[vertexIndex];
			aiVector3D& normal = mesh->mNormals[vertexIndex];
			aiVector3D& texcoord = mesh->mTextureCoords[0][vertexIndex];

			// 右手系 -> 左手系への変換
			datas_.meshData_.vertices[vertexIndex].position = { -position.x, position.y, position.z, 1.0f };
			datas_.meshData_.vertices[vertexIndex].normal = { -normal.x, normal.y, normal.z };
			datas_.meshData_.vertices[vertexIndex].texCoord = { texcoord.x, texcoord.y };
		}

		// Indexを解析する
		for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex) {
			aiFace& face = mesh->mFaces[faceIndex];
			assert(face.mNumIndices == 3);

			for (uint32_t element = 0; element < face.mNumIndices; ++element) {
				uint32_t vertexIndex = face.mIndices[element];
				datas_.meshData_.indices.push_back(vertexIndex);
			}
		}
	}
}


/// <summary>
/// MaterialDataの解析
/// </summary>
void Model::ParseMaterialData(const aiScene* scene, const std::string& filePath)
{
	for (uint32_t materialIndex = 0; materialIndex < scene->mNumMaterials; ++materialIndex) {
		aiMaterial* material = scene->mMaterials[materialIndex];

		if (material->GetTextureCount(aiTextureType_DIFFUSE) != 0) {
			aiString textureFilePath;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &textureFilePath);

			// FileFormatで読み込みパスの分岐
			if (datas_.fileFormat_ == ModelFileFormat::OBJ.first) {
				datas_.materialData_.textureHandle = TextureManager::LoadTexture("Obj/" + filePath, textureFilePath.C_Str());
			}
			else if (datas_.fileFormat_ == ModelFileFormat::GLTF.first) {
				datas_.materialData_.textureHandle = TextureManager::LoadTexture("gLTF/" + filePath, textureFilePath.C_Str());
			}
		}

		// マテリアルの名前の設定
		// 複数マテリアルは今は非対応。ファイルの名前をそのままマテリアルの名前へ
		datas_.materialData_.name = material->GetName().C_Str();
	}
}


/// <summary>
/// BufferResourceの生成
/// </summary>
void Model::CreateBufferResource()
{
	// mesh
	buffers_.meshBuffer_.CreateResource(UINT(datas_.meshData_.vertices.size()));
	// vertexBufferView
	buffers_.vertexBuffer_.CreateResource(UINT(datas_.meshData_.vertices.size()));
	buffers_.vertexBuffer_.CreateVertexBufferView();
	// indexBufferView
	buffers_.indecesBuffer_.CreateResource(UINT(datas_.meshData_.indices.size()));
	buffers_.indecesBuffer_.CreateIndexBufferView();
	// material
	buffers_.materialBuffer_.CreateResource();
	// transform
	buffers_.transformBuffer_.CreateResource();
	// light
	buffers_.lightBuffer_.CreateResource();
}


/// <summary>
/// コマンドコール
/// </summary>
void Model::CommandCall(Camera* camera)
{
	// Commandの取得
	Commands commands = CommandManager::GetInstance()->GetCommands();

	// PipeLineCheck
	PipeLineManager::PipeLineCheckAndSet(PipeLineType::Object3D);

	// VertexBufferView
	buffers_.vertexBuffer_.IASetVertexBuffers(1);
	// IndexBufferView
	buffers_.indecesBuffer_.IASetIndexBuffer();
	// Material
	buffers_.materialBuffer_.CommandCall(0);
	// TransformationMatrix
	buffers_.transformBuffer_.CommandCall(1);
	// Camera
	commands.List->SetGraphicsRootConstantBufferView(2, camera->constBuffer->GetGPUVirtualAddress());
	// Texture
	SRVManager::SetGraphicsRootDescriptorTable(3, datas_.materialData_.textureHandle);
	// Light
	buffers_.lightBuffer_.CommandCall(4);
	// Draw!!
	commands.List->DrawIndexedInstanced(UINT(datas_.meshData_.indices.size()), 1, 0, 0, 0);
}
