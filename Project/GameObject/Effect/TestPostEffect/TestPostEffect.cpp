#include "TestPostEffect.h"



// 初期化処理
void TestPostEffect::Initialize()
{

	// リソースなどを作成
	Create();
}


// 更新処理
void TestPostEffect::Update()
{

#ifdef _DEBUG

	if (ImGui::TreeNode("TestEffect")) {


		ImGui::TreePop();
	}

#endif // _DEBUG

}


// 描画処理
void TestPostEffect::Draw()
{

	// コマンドコール
	CommandCall();
}
