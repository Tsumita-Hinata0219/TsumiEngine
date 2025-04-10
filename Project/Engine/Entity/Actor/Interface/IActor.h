#pragma once

#include "Math/MyMath.h"
#include "../../TransformNode/Node/TransformNode.h"

// 前方宣言
class IComponent;
class IRenderComponent;
//class GameEntityManager;

/* ゲーム内オブジェクトの基底クラス */
class IActor : public std::enable_shared_from_this<IActor> {

public:

    // 状態
    enum class State {
        None = -1,
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
    virtual void Init() {};

    /// <summary>
    /// 更新処理関係
    /// </summary>
    void Update(float deltaTime);
    void UpdateComponents(float deltaTime);
    virtual void UpdateActor([[maybe_unused]]float deltaTime) {};

    /// <summary>
    /// 描画処理
    /// </summary>
    void Render();

    /// <summary>
    /// Componentの追加
    /// </summary>
    void AddComponent(std::shared_ptr<IComponent> component);

    /// <summary>
    /// RenderComponentの追加
    /// </summary>
    void AddComponent(std::shared_ptr<IRenderComponent> component);

    /// <summary>
	/// ComponentのWeakPtr取得
    /// </summary>
    std::weak_ptr<IComponent> GetComponent(const std::string& name);

    /// <summary>
    /// RenderComponentのWeakPtr取得
    /// </summary>
    std::weak_ptr<IRenderComponent> GetRenderComponent();


#pragma region Accessor 

	// 状態
	State GetState() const { return state_; }
	void SetState(State state) { state_ = state; }
    
    // 名前
    std::string GetName() const { return name_; }

	// TransformNode
	std::weak_ptr<TransformNode> GetTransformNode() const { return transNode_; }

    // 描画フラグ
    void ToggleRender(bool state) { isRender_ = state; }

    // 親マネージャー
	//void SetManager(GameEntityManager* pManager) { pManager_ = pManager; }

#pragma endregion 


private:

    /// <summary>
    /// 共有ポインタを取得する関数
    /// </summary>
    /// <returns></returns>
    std::shared_ptr<IActor> GetSharedPtr() {
        return shared_from_this();
    }


protected:

    // 名前
    std::string name_;

    // 状態
    State state_;

    // Transform
    std::shared_ptr<TransformNode> transNode_;

    // ComponentList
	std::unordered_map<std::string, std::shared_ptr<IComponent>> componentMap_;

    // 描画フラグ
	bool isRender_ = false;
	// 描画コンポーネント : 1つのActorが持てるRenderは1つまで
	std::shared_ptr<IRenderComponent> renderComponent_;

	// 親マネージャー
	//GameEntityManager* pManager_ = nullptr;

};
