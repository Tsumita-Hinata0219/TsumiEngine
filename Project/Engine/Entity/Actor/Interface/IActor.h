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
    virtual ~IActor();

    /// <summary>
    /// 初期化処理
    /// </summary>
    virtual void Init(std::string name = "") = 0;

    /// <summary>
    /// 更新処理関係
    /// </summary>
    void Update(float deltaTime);
    void UpdateComponents(float deltaTime);
    virtual void UpdateActor(float deltaTime);

    /// <summary>
    /// 描画処理
    /// </summary>
    void Render();

    /// <summary>
    /// コンポーネントの追加
    /// </summary>
    void AddComponent(std::shared_ptr<IComponent> component);

    /// <summary>
    /// Renderコンポーネントの追加
    /// </summary>
    void AddRenderComponent(std::shared_ptr<IComponent> component);
    
    /// <summary>
    /// コンポーネント削除
    /// </summary>
    void RemoveComponent(std::shared_ptr<IComponent> component);


#pragma region Accessor 
    
    // 名前
    std::string Get_Name() const { return name_; }

    // Transform
    Transform Get_Transform() const { return transform_; }

#pragma endregion 


private:

    // 名前
    std::string name_;

    // 状態
    State state_;

    // Transform
    Transform transform_{};

    // ComponentList
    std::vector<std::shared_ptr<IComponent>> components_;
    std::vector<std::shared_ptr<IComponent>> renderComponent_;

    // 親シーン
    IScene *pScene_ = nullptr;
};
