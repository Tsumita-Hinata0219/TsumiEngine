#include "IGLTFState.h"
#include "GameObject/Camera/Manager/CameraManager.h"


// コンストラクタ
IGLTFState::IGLTFState(ModelDatas datas)
{
	// CameraManagerのインスタンスの取得
	cameraManager_ = CameraManager::GetInstance();

	// ステートタイプの設定
	stateType_ = GLTF;

	// ModelDatasの設定
	datas_ = datas;

	// DatasをもとにBufferを作成
	CreateBufferResource(datas_);
}

// 描画処理
void IGLTFState::Draw(Transform& transform)
{
	// CameraResourceの取得
	auto cameraResource = cameraManager_->GetResource();

	// 諸々の計算
	transform.UpdateMatrix();
	transform.transformationMatData.World = transform.matWorld;
	transform.transformationMatData.WVP =
		transform.transformationMatData.World * cameraResource->viewMatrix * cameraResource->projectionMatrix;
	transform.transformationMatData.WorldInverseTranspose = Transpose(Inverse(transform.matWorld));

	// ここで書き込み
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


// コマンドコール
void IGLTFState::CommandCall()
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
	buffers_.material.GraphicsCommandCall(0);
	// TransformationMatrix
	buffers_.transform.GraphicsCommandCall(1);
	// Camera
	cameraManager_->CommandCall(2);
	// MaterialTexture
	//SRVManager::SetGraphicsRootDescriptorTable(3, datas_.material.textureHandle);
	buffers_.material.GraphicsCommandCallSRV(3, datas_.material.textureHandle);
	// Light
	buffers_.light.GraphicsCommandCall(4);
	// Environment
	buffers_.enviroment.GraphicsCommandCall(5);
	// EnvironmentTexture
	//SRVManager::SetGraphicsRootDescriptorTable(6, datas_.environment.textureHandle);
	buffers_.material.GraphicsCommandCallSRV(6, datas_.environment.textureHandle);
	// Draw!!
	commands.List->DrawIndexedInstanced(UINT(datas_.mesh.indices.size()), 1, 0, 0, 0);
}
