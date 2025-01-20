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
    /// 純粋仮想関数 : 初期化処理
    /// </summary>
    virtual void Init() = 0;

    /// <summary>
    /// 純粋仮想関数 : 更新処理
    /// </summary>
    virtual void Update() = 0;

    /// <summary>
    /// 純粋仮想関数 : 描画処理
    /// </summary>
    virtual void Draw2DFront() = 0;


private:

    // テクスチャハンドル
    uint32_t textureHandle_ = 0;

    // スプライト
    std::unique_ptr<Sprite> sprite_;

    // トランスフォーム
    Transform trans_{};

};
