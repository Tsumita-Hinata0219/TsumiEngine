#include "IOBJState.h"
#include "GameObject/Camera/Manager/CameraManager.h"


// コンストラクタ
IOBJState::IOBJState(ModelDatas datas)
{
	// CameraManagerのインスタンスの取得
	cameraManager_ = CameraManager::GetInstance();

	// ステートタイプの設定
	stateType_ = OBJ;

	// ModelDatasの設定
	datas_ = datas;

	// DatasをもとにBufferを作成
	CreateBufferResource(datas_);
}


// 描画処理
void IOBJState::Draw(Transform& transform)
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
	buffers_.indices.Map();
	buffers_.indices.WriteData(datas_.mesh.indices.data());
	buffers_.indices.UnMap();
	// Transform
	buffers_.transform.Map();
	buffers_.transform.WriteData((&transform.transformationMatData));
	buffers_.transform.UnMap();
	// Material
	buffers_.material.Map();
	buffers_.material.WriteData(&datas_.material);
	buffers_.material.UnMap();
	// Light
	buffers_.light.Map();
	buffers_.light.WriteData(&datas_.light);
	buffers_.light.UnMap();
	// Environment
	buffers_.enviroment.Map();
	buffers_.enviroment.WriteData(&datas_.environment);
	buffers_.enviroment.UnMap();
	// ColorAddition
	buffers_.colorAddition.Map();
	buffers_.colorAddition.WriteData(&datas_.colorAddition);
	buffers_.colorAddition.UnMap();

	// コマンドコール
	CommandCall();
}


// コマンドコール
void IOBJState::CommandCall()
{
	// Commandの取得
	Commands commands = CommandManager::GetInstance()->GetCommands();

	// PipeLineCheck
	PipeLineManager::PipeLineCheckAndSet(PipeLineType::Object3D);

	// VertexBufferView
	buffers_.vertex.IASetVertexBuffers(1);
	// IndexBufferView
	buffers_.indices.IASetIndexBuffer();
	// Transform
	buffers_.transform.GraphicsCommandCall(0);
	// Material
	buffers_.material.GraphicsCommandCall(1);
	// Camera
	cameraManager_->CommandCall(2);
	// Light
	buffers_.light.GraphicsCommandCall(3);
	// Environment
	buffers_.enviroment.GraphicsCommandCall(4);
	// ColorAddition
	buffers_.colorAddition.GraphicsCommandCall(5);
	// MaterialTexture
	buffers_.material.GraphicsCommandCallSRV(6, datas_.material.textureHandle);
	// EnvironmentTexture
	buffers_.material.GraphicsCommandCallSRV(7, datas_.environment.textureHandle);
	// Draw!!
	commands.List->DrawIndexedInstanced(UINT(datas_.mesh.indices.size()), 1, 0, 0, 0);
}
