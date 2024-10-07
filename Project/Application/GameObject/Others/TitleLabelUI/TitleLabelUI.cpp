#include "TitleLabelUI.h"



// 初期化処理
void TitleLabelUI::Init()
{
    // ラベルのモデルパス
    std::pair<std::string, std::string> myArray[2] = {
        {"Obj/TitleLabel/Start", "TitleLabel_Start.obj"},
        {"Obj/TitleLabel/Exsit", "TitleLabel_Exsit.obj"} 
    };

    // ラベル配列のresize
    labelObjs_.resize(EnumSize<TitleLabelType>::value);

    // ラベルのベースの座標の設定　
    labelBasePos_ = { 0.0f, -2.0f, 20.0f };
    // ラベルのオフセット
    labelOffset_ = { 0.0f, 0.5f, 0.0f };

    // ラベルオブジェクトの初期化
    for (int i = 0; i < labelObjs_.size(); ++i) {
        labelObjs_[i] = std::make_unique<TitleLabelObject>(myArray[i]);
        labelObjs_[i]->Init();
        labelObjs_[i]->SetPosition(labelBasePos_ + labelOffset_);
        labelOffset_ *= -1.0f;
    }
}


// 更新処理
void TitleLabelUI::Update()
{
    for (auto& element : labelObjs_) {
        element->Update();
    }
}


// 描画処理
void TitleLabelUI::Draw3D()
{
    for (auto& element : labelObjs_) {
        element->Draw3D();
    }
}
void TitleLabelUI::Draw2DFront()
{
}
void TitleLabelUI::Draw2DBack()
{
}

