#include "ModelObjState.h"
#include "Model.h"


/// <summary>
/// 初期化処理
/// </summary>
void ModelObjState::Initialize(Model* pModel) {

	pModel;

	modelData_.material = pModel->GetObjData().material;
	modelData_.vertices = pModel->GetObjData().vertices;

	// リソースの作成
	//modelData_ = LoadObjFile(pModel, pModel->GetObjDirectoryPath());
	resource_.Vertex = CreateResource::CreateBufferResource(sizeof(VertexData) * modelData_.vertices.size());
	resource_.Material = CreateResource::CreateBufferResource(sizeof(Material));
	resource_.Lighting = CreateResource::CreateBufferResource(sizeof(DirectionalLight));
	resource_.VertexBufferView = CreateResource::CreateVertexBufferView(sizeof(VertexData) * modelData_.vertices.size(), resource_.Vertex.Get(), int(modelData_.vertices.size()));
}


/// <summary>
/// 描画処理
/// </summary>
void ModelObjState::Draw(Model* pModel, WorldTransform worldTransform, ViewProjection view) {

	VertexData* vertexData = nullptr;
	Material* material = nullptr;
	DirectionalLight* lightData = nullptr;


	// 書き込むためにアドレスを取得
	resource_.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	resource_.Material->Map(0, nullptr, reinterpret_cast<void**>(&material));
	resource_.Lighting->Map(0, nullptr, reinterpret_cast<void**>(&lightData));


	// 頂点データをリソースにコピー
	std::memcpy(vertexData, modelData_.vertices.data(), sizeof(VertexData) * modelData_.vertices.size());

	// マテリアルの情報を書き込む
	material->color = pModel->GetColor();

	// ライティングの設定
	lightData->color = pModel->GetDirectionalLight().color;
	lightData->direction = pModel->GetDirectionalLight().direction;
	lightData->intensity = pModel->GetDirectionalLight().intensity;


	// コマンドコール
	CommandCall(pModel->GetObjData().textureHD, worldTransform, view);
}


/// <summary>
/// コマンドコール処理
/// </summary>
void ModelObjState::CommandCall(uint32_t texture, WorldTransform worldTransform, ViewProjection view) {

	// RootSignatureを設定。
	DirectXCommon::GetInstance()->GetCommandList()->SetGraphicsRootSignature(LightGraphicPipeline::GetInstance()->GetPsoProperty().rootSignature);
	// PSOを設定
	DirectXCommon::GetInstance()->GetCommandList()->SetPipelineState(LightGraphicPipeline::GetInstance()->GetPsoProperty().graphicsPipelineState);

	///// いざ描画！！！！！
	// VBVを設定
	DirectXCommon::GetInstance()->GetCommandList()->IASetVertexBuffers(0, 1, &resource_.VertexBufferView);

	// 形状を設定
	DirectXCommon::GetInstance()->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// CBVを設定する
	DirectXCommon::GetInstance()->GetCommandList()->SetGraphicsRootConstantBufferView(0, resource_.Material->GetGPUVirtualAddress());

	// wvp用のCBufferの場所を設定
	DirectXCommon::GetInstance()->GetCommandList()->SetGraphicsRootConstantBufferView(1, worldTransform.constBuffer->GetGPUVirtualAddress());

	// View用のCBufferの場所を設定
	DirectXCommon::GetInstance()->GetCommandList()->SetGraphicsRootConstantBufferView(2, view.constBuffer->GetGPUVirtualAddress());

	// DescriptorTableを設定する
	if (!texture == 0) {
		DescriptorManager::SetGraphicsRootDescriptorTable(3, texture);
	}

	// 光用のCBufferの場所を設定
	DirectXCommon::GetInstance()->GetCommandList()->SetGraphicsRootConstantBufferView(4, resource_.Lighting->GetGPUVirtualAddress());

	// 描画！(DrawCall / ドローコール)。3頂点で1つのインスタンス。インスタンスについては今後
	DirectXCommon::GetInstance()->GetCommandList()->DrawInstanced(UINT(modelData_.vertices.size()), 1, 0, 0);
}


/// <summary>
/// Objのファイルを読み込む
/// </summary>
ModelData ModelObjState::LoadObjFile(Model* pModel, const std::string& directoryPath) {

	/* 1. 中で必要となる変数の宣言 */

	ModelData modelData;            // 構築するModelData
	std::vector<Vector4> positions; // 位置
	std::vector<Vector3> normals;   // 法線
	std::vector<Vector2> texcoords; // テクスチャ座標
	std::string line;               // ファイルから読んだ１行をを格納するもの



	/* 2. ファイルを開く */

	// ファイルを開く
	std::ifstream file("Resources/Obj/" + directoryPath + "/" + directoryPath + ".obj");
	// とりあえず開けなかったら止める
	assert(file.is_open());



	/* 3. 実際にファイルを読み、ModelDataを構築していく */

	while (std::getline(file, line)) {

		std::string identifier;
		std::istringstream s(line);

		// 先頭の識別子を読む
		s >> identifier;


		// identifierに応じた処理
		// "v"  = 頂点位置
		// "vt" = 頂点テクスチャ座標 
		// "vn" = 頂点法線
		// "f"  = 面

		if (identifier == "v") {

			Vector4 position{};
			s >> position.x >> position.y >> position.z;
			position.x *= -1.0f;
			position.w = 1.0f;
			positions.push_back(position);
		}
		else if (identifier == "vt") {

			Vector2 texcoord{};
			s >> texcoord.x >> texcoord.y;
			texcoord.y *= -1.0f;
			texcoords.push_back(texcoord);
		}
		else if (identifier == "vn") {

			Vector3 normal{};
			s >> normal.x >> normal.y >> normal.z;
			normal.x *= -1.0f;
			normals.push_back(normal);
		}
		else if (identifier == "f") {

			VertexData triangle[3]{};

			// 面は三角形限定。その他は未対応
			for (int32_t faceVertex = 0; faceVertex < 3; ++faceVertex) {

				std::string vertexDefinition;
				s >> vertexDefinition;

				// 頂点の要素へのIndexは「位置/UV/法線」で格納されているので、分解してIndexを取得する
				std::istringstream v(vertexDefinition);
				uint32_t elementIndex[3]{};

				for (int32_t element = 0; element < 3; ++element) {

					std::string index;
					std::getline(v, index, '/'); // "/"区切りでインデックスを読んでいく
					elementIndex[element] = std::stoi(index);
				}

				// 要素へのIndexから、実際の要素の値を取得して、頂点を構築する
				Vector4 position = positions[static_cast<std::vector<Vector4, std::allocator<Vector4>>::size_type>(elementIndex[0]) - 1];
				Vector2 texcoord = texcoords[static_cast<std::vector<Vector2, std::allocator<Vector2>>::size_type>(elementIndex[1]) - 1];
				Vector3 normal = normals[static_cast<std::vector<Vector3, std::allocator<Vector3>>::size_type>(elementIndex[2]) - 1];
				triangle[faceVertex] = { position, texcoord, normal };
			}
			// 頂点を逆順で登録することで、回利潤を逆にする
			modelData.vertices.push_back(triangle[2]);
			modelData.vertices.push_back(triangle[1]);
			modelData.vertices.push_back(triangle[0]);
		}
		else if (identifier == "mtllib") {

			// materialTemplateLibraryファイルの名前を取得する
			std::string materialFileName;
			s >> materialFileName;

			// 基本的にobjファイルを同じ階層にmtlは存在させるので、ディレクトリファイル名を渡す
			modelData.material = LoadMaterialTemplateFile(directoryPath, materialFileName);
		}
	}
	// テクスチャを指定されたものにする
	uint32_t texHandle = TextureManager::LoadTexture(modelData.material.textureFilePath, true);
	pModel->SetTexHandle(texHandle);

	/* 4. Modeldataを返す */
	return modelData;

}


/// <summary>
/// mtlファイルを読み込む関数
/// </summary>
MaterialData ModelObjState::LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename) {

	/* 1. 中で必要となる変数の宣言 */

	MaterialData materialData{}; // 構築するMaterialData
	std::string line{};			 // ファイルから読んだ１行を格納するもの



	/* 2. ファイルを開く */

	// ファイルを開く
	std::ifstream file("Resources/Obj/" + directoryPath + "/" + filename);

	//とりあえず開けなかったら止める
	assert(file.is_open());



	/* 3. 実際にファイルを読み、MaterualDataを構築していく */

	while (std::getline(file, line)) {

		std::string identifier{};
		std::istringstream s(line);
		s >> identifier;


		// identifierに応じた処理
		// "map_Kd" = textureのファイル名が記載されている

		if (identifier == "map_Kd") {

			std::string textureFileName{};
			s >> textureFileName;

			// 連結してファイルパスにする
			materialData.textureFilePath = "Resources/Obj/" + directoryPath + "/" + textureFileName;
		}
	}



	/* 4. MaterialData を返す */
	return materialData;
}

