#include "IOBJState.h"
#include "Camera/Manager/CameraManager.h"


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
	buffers_.vertex.UpdateData(datas_.mesh.vertices.data());
	// IBV
	buffers_.indices.UpdateData(datas_.mesh.indices.data());
	// Transform
	buffers_.transform.UpdateData((&transform.transformationMatData));
	// Material
	buffers_.material.UpdateData(&datas_.material);
	// Light
	buffers_.light.UpdateData(&datas_.light);
	// Environment
	buffers_.enviroment.UpdateData(&datas_.environment);
	// ColorAddition
	buffers_.colorAddition.UpdateData(&datas_.colorAddition);

	// コマンドコール
	CommandCall();
}


// コマンドコール
void IOBJState::CommandCall()
{
	// Commandの取得
	Commands commands = CommandManager::GetInstance()->GetCommands();

	// PipeLineCheck
	if (renderState_ == RenderState::None) {
		PipeLineManager::SetPipeLine(PipeLine::Container::Graphic, PipeLine::Category::Object3D, PipeLine::SubFilter::Cull_Mode_Back);
	}
	else if (renderState_ == RenderState::CullingMode_None) {
		PipeLineManager::SetPipeLine(PipeLine::Container::Graphic, PipeLine::Category::Object3D, PipeLine::SubFilter::Cull_Mode_None);
	}
	else if (renderState_ == RenderState::DepthWriteMask_ZERO) {
		PipeLineManager::SetPipeLine(PipeLine::Container::Graphic, PipeLine::Category::Object3D, PipeLine::SubFilter::DepthWriteMask_Zero);
	}

	// VertexBufferView
	buffers_.vertex.IASetVertexBuffers(1);
	// IndexBufferView
	buffers_.indices.IASetIndexBuffer();
	// Transform
	buffers_.transform.BindGraphicsCBV(0);
	// Material
	buffers_.material.BindGraphicsCBV(1);
	// Camera
	cameraManager_->CommandCall(2);
	// Light
	buffers_.light.BindGraphicsCBV(3);
	// Environment
	buffers_.enviroment.BindGraphicsCBV(4);
	// ColorAddition
	buffers_.colorAddition.BindGraphicsCBV(5);
	// MaterialTexture
	buffers_.material.BindGraphicsSRV(6, datas_.material.textureHandle);
	// EnvironmentTexture
	buffers_.material.BindGraphicsSRV(7, datas_.environment.textureHandle);
	// Draw!!
	commands.List->DrawIndexedInstanced(UINT(datas_.mesh.indices.size()), 1, 0, 0, 0);
}
