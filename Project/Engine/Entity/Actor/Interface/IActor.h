#pragma once

#include "Math/MyMath.h"
#include "Scene/IScene.h"
#include "../../TransformNode/Node/TransformNode.h"

// 前方宣言
class IComponent;
class IRenderComponent;

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
    /// 生成
    /// </summary>
    void Create(std::string name = "");

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
    /// 描画処理
    /// </summary>
    void Render();

    /// <summary>
    /// Componentの追加
    /// </summary>
    void Add_Component(std::shared_ptr<IComponent> component);

    /// <summary>
    /// RenderComponentの追加
    /// </summary>
    void Add_RenderComponent(std::weak_ptr<IRenderComponent> component);

    /// <summary>
	/// ComponentのWeakPtr取得
    /// </summary>
    std::weak_ptr<IComponent> Get_Component(const std::string& name);


#pragma region Accessor 

	// 状態
	State Get_State() const { return state_; }
	void Set_State(State state) { state_ = state; }
    
    // 名前
    std::string Get_Name() const { return name_; }

    // 描画フラグ
    void Toggle_Render(bool state) { isRender_ = state; }

#pragma endregion 


private:

    // 名前
    std::string name_;

    // 状態
    State state_;

    // Transform
    std::weak_ptr<TransformNode> transNode_;

    // ComponentList
	std::unordered_map<std::string, std::shared_ptr<IComponent>> componentMap_;

    // 描画フラグ
	bool isRender_ = false;
	// 描画コンポーネント : 1つのActorが持てるRenderは1つまで
	std::weak_ptr<IRenderComponent> renderComponent_;

    // 親シーン
    IScene *pScene_ = nullptr;
};
