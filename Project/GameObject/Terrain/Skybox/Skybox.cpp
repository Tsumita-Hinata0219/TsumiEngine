#include "Skybox.h"



// 初期化処理
void Skybox::Initialize()
{
	// モデルの読み込み
	model_ = make_unique<Model>();
	model_->CreateFromObjAssimpVer("Skybox", "Skybox");

	// テクスチャの読み込み
	this->texture_ = TextureManager::LoadTexture("Texture", "airport_4k.dds");

	// Scale
	initScale_ = 100.0f;

	// Transformの初期化処理
	transform_.Initialize();
	transform_.srt.scale = { initScale_, initScale_, initScale_ };


	// リソースの作成
	resource_.Vertex = CreateResource::CreateBufferResource(sizeof(VertexData) * model_->GetObjData().vertices.size());
	resource_.Material = CreateResource::CreateBufferResource(sizeof(Material));
	resource_.Lighting = CreateResource::CreateBufferResource(sizeof(DirectionalLight));
	resource_.VertexBufferView = CreateResource::CreateVertexBufferView(sizeof(VertexData) * model_->GetObjData().vertices.size(), resource_.Vertex.Get(), int(model_->GetObjData().vertices.size()));
	resource_.Index = CreateResource::CreateBufferResource(sizeof(uint32_t) * model_->GetObjData().indices.size());
	resource_.IndexBufferView = CreateResource::CreateIndexBufferview(sizeof(uint32_t) * model_->GetObjData().indices.size(), resource_.Index.Get());
}


// 更新処理
void Skybox::Update()
{
	// Transformの更新
	transform_.UpdateMatrix();


#ifdef _DEBUG

	if (ImGui::TreeNode("Skybox")) {

		ImGui::DragFloat3("Scale", &transform_.srt.scale.x, 0.1f);
		ImGui::DragFloat3("Rotate", &transform_.srt.rotate.x, 0.1f);
		ImGui::DragFloat3("Translate", &transform_.srt.translate.x, 0.1f);

		ImGui::TreePop();
	}


#endif // _DEBUG
}


// 描画処理
void Skybox::Draw(Camera* camera)
{
	VertexData* vertexData = nullptr;
	Material* material = nullptr;
	uint32_t* indexData = nullptr;


	// 書き込むためにアドレスを取得
	resource_.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	resource_.Material->Map(0, nullptr, reinterpret_cast<void**>(&material));
	resource_.Index->Map(0, nullptr, reinterpret_cast<void**>(&indexData));


	// 頂点データをリソースにコピー
	std::memcpy(vertexData, model_->GetObjData().vertices.data(), sizeof(VertexData) * model_->GetObjData().vertices.size());
	std::memcpy(indexData, model_->GetObjData().indices.data(), sizeof(uint32_t) * model_->GetObjData().indices.size());


	// マテリアルの情報を書き込む
	material->color = model_->GetColor();


	// コマンドコール
	CommandCall(camera);
}


// コマンドコール
void Skybox::CommandCall(Camera* camera)
{
	// コマンドの取得
	Commands commands = CommandManager::GetInstance()->GetCommands();

	// PipeLineCheck
	PipeLineManager::PipeLineCheckAndSet(PipeLineType::Skybox);

	///// いざ描画！！！！！
	// 頂点の設定
	commands.List->IASetVertexBuffers(0, 1, &resource_.VertexBufferView);
	commands.List->IASetIndexBuffer(&resource_.IndexBufferView);

	// CBVを設定する
	commands.List->SetGraphicsRootConstantBufferView(0, resource_.Material->GetGPUVirtualAddress());

	// wvp用のCBufferの場所を設定
	commands.List->SetGraphicsRootConstantBufferView(1, transform_.constBuffer->GetGPUVirtualAddress());

	// View用のCBufferの場所を設定
	commands.List->SetGraphicsRootConstantBufferView(2, camera->constBuffer->GetGPUVirtualAddress());

	// DescriptorTableを設定する
	if (!texture_ == 0) {
		SRVManager::SetGraphicsRootDescriptorTable(3, texture_);
	}

	// 描画！(DrawCall / ドローコール)。
	commands.List->DrawIndexedInstanced(UINT(model_->GetObjData().indices.size()), 1, 0, 0, 0);
}
