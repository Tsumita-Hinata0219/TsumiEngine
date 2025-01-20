#pragma once


/* 操作UIマネージャー */
class OperationUIManager {

public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    OperationUIManager() = default;

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~OperationUIManager() = default;

    /// <summary>
    /// 初期化処理
    /// </summary>
    void Init();

    /// <summary>
    /// 更新処理
    /// </summary>
    void Update();

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw2DFront();


private:



};
