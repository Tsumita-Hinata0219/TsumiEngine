#include "TestPostEffect.h"



// 初期化処理
void TestPostEffect::Initialize()
{
	// リソースなどを作成
	Create();
	effectType_ = IPostEffect::Type::OutLine;
}


// 更新処理
void TestPostEffect::Update()
{



#ifdef _DEBUG

	// ImGuiの描画
	DrawImGui();

#endif // _DEBUG
}


// 描画処理
void TestPostEffect::Draw(Camera* camera)
{

	// コマンドコール
	CommandCall(camera);
}
