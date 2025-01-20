#pragma once

#include "GameObject/GameObject.h"

/* 操作UIクラスの基底クラス */
class IOperationUI {

public:
    /// <summary>
    /// 仮想デストラクタ
    /// </summary>
    virtual ~IOperationUI() = default;

    /// <summary>
    /// 初期化処理
    /// </summary>
    virtual void Init();

    /// <summary>
    /// 更新処理
    /// </summary>
    virtual void Update();

    /// <summary>
    /// 描画処理
    /// </summary>
    virtual void Draw2DFront();

#pragma region Accessor アクセッサ

    // テクスチャハンドル
    virtual void SetTextureHandle(int setTexHD) {
        this->textureHandle_ = setTexHD;
    }

    // カラー
    virtual void SetColor(const Vector4& setColor) {
        this->sprite_->SetColor(setColor);
    }

#pragma endregion

private:
    // テクスチャハンドル
    uint32_t textureHandle_ = 0;

    // スプライト
    std::unique_ptr<Sprite> sprite_;

    // トランスフォーム
    Transform trans_{};
};
