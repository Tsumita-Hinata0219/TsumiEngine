#include "TitleUIManager.h"



// 初期化処理
void TitleUIManager::Init()
{
    /* ----- GameNameBar ゲーム名 ----- */
    gameName_ = std::make_unique<GameNameBar>();
    gameName_->Init();


    /* ----- TitleLabelType ラベル ----- */
    // ラベルのモデルパス
    std::pair<std::string, std::string> myArray[2] = {
        {"Obj/TitleLabel/Start", "TitleLabel_Start.obj"},
        {"Obj/TitleLabel/Exsit", "TitleLabel_Exsit.obj"}
    };

    // ラベルのベースの座標の設定　
    labelBasePos_ = { 0.0f, -2.0f, 20.0f };
    // ラベルのオフセット
    labelOffset_ = { 0.0f, 0.5f, 0.0f };

    // ラベル配列のresize
    labelObjs_.resize(EnumSize<TitleLabelType>::value);
    // ラベルオブジェクトの初期化
    for (int i = 0; i < labelObjs_.size(); ++i) {
        labelObjs_[i] = std::make_unique<TitleLabelObject>(myArray[i]);
        labelObjs_[i]->Init();
        labelObjs_[i]->SetPosition(labelBasePos_ + labelOffset_);
        labelOffset_ *= -1.0f; // -1をかけて値を反転
    }


    /* ----- SelectBat セレクトバー ----- */
    selectBar_ = std::make_unique<SelectBar>();
    selectBar_->Init();
}


// 更新処理
void TitleUIManager::Update()
{
    /* ----- GameNameBar ゲーム名 ----- */
    gameName_->Update();

    /* ----- TitleLabelType ラベル ----- */
    for (auto& element : labelObjs_) {
        element->Update();
    }

    /* ----- SelectBat セレクトバー ----- */
    selectBar_->Update();
}


// 描画処理
void TitleUIManager::Draw3D()
{
    /* ----- GameNameBar ゲーム名 ----- */
    gameName_->Draw3D();

    /* ----- TitleLabelType ラベル ----- */
    for (auto& element : labelObjs_) {
        element->Draw3D();
    }

    /* ----- SelectBat セレクトバー ----- */
    selectBar_->Draw3D();
}
void TitleUIManager::Draw2DFront()
{
}
void TitleUIManager::Draw2DBack()
{
}

