#include "IOperationUI.h"

/// <summary>
/// 初期化処理
/// </summary>
void IOperationUI::Init() 
{
    // スプライトの初期化
    sprite_ = std::make_unique<Sprite>();
    sprite_->SetTexture(textureHandle_);

    // トランスフォームの初期化
    trans_.Init();
}


/// <summary>
/// 更新処理
/// </summary>
void IOperationUI::Update() 
{


}


/// <summary>
/// 描画処理
/// </summary>
void IOperationUI::Draw2DFront() 
{ 
    sprite_->Draw(trans_); 
}
