#include "RenderState .h"
#include "Camera/Manager/CameraManager.h"
#include "PipeLineManager/PipeLineManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
RenderSystem::RenderState::RenderState()
{
	datas_ = std::make_unique<RenderSystem::Rendering::Datas>();
	buffers_ = std::make_unique<RenderSystem::Rendering::Buffers>();

	cameraManager_ = CameraManager::GetInstance();
	pipeLine_ = PipeLineManager::GetInstance();
}


/// <summary>
/// 描画処理
/// </summary>
void RenderSystem::RenderState::Draw3D()
{
	// 描画データの更新
	Update_RenderData();
	// PipeLineのチェック
	Check_PipeLine();
	// 描画データのバインド
	Bind_RenderData();
	// Draw!
	Execute_DrawCommand();
}


/// <summary>
/// Buffer生成
/// </summary>
void RenderSystem::RenderState::Create_RenderBuffer()
{
	// mesh
	buffers_->mesh.CreateCBV(UINT(datas_->mesh.vertices.size()));

	// VBV
	buffers_->vertex.CreateCBV(UINT(datas_->mesh.vertices.size()));
	buffers_->vertex.CreateVertexBufferView();

	// IBV
	buffers_->indices.CreateCBV(UINT(datas_->mesh.indices.size()));
	buffers_->indices.CreateIndexBufferView();
	
	// Transform
	buffers_->transform.CreateCBV();

	// Material
	buffers_->material.CreateCBV();

	// Light
	buffers_->light.CreateCBV();

	// Environment
	buffers_->enviroment.CreateCBV();

	// ColorAddition
	buffers_->colorAddition.CreateCBV();
}


/// <summary>
/// 描画データのバインド
/// </summary>
void RenderSystem::RenderState::Update_RenderData()
{
	// VBV
	buffers_->vertex.UpdateData(datas_->mesh.vertices.data());

	// IBV
	buffers_->indices.UpdateData(datas_->mesh.indices.data());

	// Transform
	//buffers_->transform.UpdateData((&transform.transformationMatData));

	// Material
	buffers_->material.UpdateData(&datas_->material);

	// Light
	buffers_->light.UpdateData(&datas_->light);

	// Environment
	buffers_->enviroment.UpdateData(&datas_->environment);

	// ColorAddition
	buffers_->colorAddition.UpdateData(&datas_->colorAddition);
}


/// <summary>
/// PipeLineのチェック
/// </summary>
void RenderSystem::RenderState::Check_PipeLine()
{
	int a = 0;

	if (a == 0) { // 背面カリング
		pipeLine_->SetPipeLine(PipeLine::Container::Graphic, 
			PipeLine::Category::Object3D, PipeLine::SubFilter::Cull_Mode_Back);
	}
	else if (a == 2) { // カリングなし
		pipeLine_->SetPipeLine(PipeLine::Container::Graphic, 
			PipeLine::Category::Object3D, PipeLine::SubFilter::Cull_Mode_None);
	}
	else if (a == 3) { // ワイヤーフレーム
		pipeLine_->SetPipeLine(PipeLine::Container::Graphic, 
			PipeLine::Category::Object3D, PipeLine::SubFilter::Fill_Mode_Wireframe);
	}
	else if (a == 4) { // Depth 0
		pipeLine_->SetPipeLine(PipeLine::Container::Graphic, 
			PipeLine::Category::Object3D, PipeLine::SubFilter::DepthWriteMask_Zero);
	}
}


/// <summary>
/// 描画データのバインド
/// </summary>
void RenderSystem::RenderState::Bind_RenderData()
{
	// VBV
	buffers_->vertex.IASetVertexBuffers(1);

	// IBV
	buffers_->indices.IASetIndexBuffer();

	// Transform
	buffers_->transform.BindGraphicsCBV(1);

	// Material
	buffers_->material.BindGraphicsCBV(2);

	// Camera
	cameraManager_->Bind_CameraData(2);

	// Light
	buffers_->light.BindGraphicsCBV(3);

	// Environment
	buffers_->enviroment.BindGraphicsCBV(4);

	// ColorAddition
	buffers_->colorAddition.BindGraphicsCBV(5);

	// Material Texture
	buffers_->material.BindGraphicsSRV(6, datas_->material.textureHandle);

	// Environment Texture
	buffers_->material.BindGraphicsSRV(7, datas_->environment.textureHandle);
}


/// <summary>
/// 描画
/// </summary>
void RenderSystem::RenderState::Execute_DrawCommand()
{
	// Commandの取得
	Commands commands = CommandManager::GetInstance()->GetCommands();
	// Draw!!
	commands.List->DrawIndexedInstanced(UINT(datas_->mesh.indices.size()), 1, 0, 0, 0);
}
