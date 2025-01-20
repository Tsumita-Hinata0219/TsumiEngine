#include "OperationUIManager.h"


/// <summary>
/// 初期化処理
/// </summary>
void OperationUIManager::Init() 
{
    const int size = EnumSize<OperationUIType>::value;

    // テクスチャの読み込み
    std::string rootPath = "Texture/Game/Operation_UI";
    int texHDs[size] = {
        TextureManager::LoadTexture(rootPath, "Cont_Frame.png"),
        TextureManager::LoadTexture(rootPath, "Cont_Line.png"),
        TextureManager::LoadTexture(rootPath, "OP_LStick.png"),
        TextureManager::LoadTexture(rootPath, "OP_RB.png"),
        TextureManager::LoadTexture(rootPath, "OP_RStick.png"),
    };

    // 配列のサイズ設定
    opUIs_.resize(size);

    // 初期化
    for (int i = 0; i < opUIs_.size(); ++i) {
        opUIs_[i] = std::make_unique<IOperationUI>();
        opUIs_[i]->SetTextureHandle(texHDs[i]);
        opUIs_[i]->Init();
    }
}


/// <summary>
/// 更新処理
/// </summary>
void OperationUIManager::Update() 
{


}


/// <summary>
/// 描画処理
/// </summary>
void OperationUIManager::Draw2DFront() 
{



}
