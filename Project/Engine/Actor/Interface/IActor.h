#pragma once

#include "Math/MyMath.h"
#include "Scene/IScene.h"
#include "Transform/Transform.h"

// 前方宣言
class IComponent;

/* ゲーム内オブジェクトの基底クラス */
class IActor {

public:
    // 状態
    enum class State {
        Active,
        Paused,
        Dead,
    };

    /// <summary>
    /// コンストラクタ
    /// </summary>
    IActor();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~IActor();

    /// <summary>
    /// 初期化処理
    /// </summary>
    virtual void Init() = 0;

    /// <summary>
    /// 更新処理関係
    /// </summary>
    void Update(float deltaTime);
    void UpdateComponents(float deltaTime);
    virtual void UpdateActor(float deltaTime);

    /// <summary>
    /// コンポーネントの追加
    /// </summary>
    void AddComponent(std::shared_ptr<IComponent> component);

private:
    // 状態
    State state;

    // Transform
    Transform transform{};

    // ComponentList
    std::vector<std::shared_ptr<IComponent>> componentList;

    // 親シーン
    IScene *pScene = nullptr;
};
