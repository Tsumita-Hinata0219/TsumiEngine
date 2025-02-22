#pragma once

#include "IObject/IObject.h"
#include "GameObject/GameObject.h"


/* ステージセレクトの操作クラス */
class StageSelectOperation {

private:
	enum class SelectionDirection {
		Previous, // 上方向
		Next      // 下方向
	};

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	StageSelectOperation() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StageSelectOperation() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();


#pragma region Accessor アクセッサ

	// 決定ボタンを押したかのフラグ
	bool IsSelect() const { return this->isSelect_; }

	// セレクトしている番号
	int GetSelectNum() const { return this->selectNum_; }

#pragma endregion 


private:

	/// <summary>
	/// セレクトの操作
	/// </summary>
	void SelectOperation();

	/// <summary>
	/// セレクトチェンジ
	/// </summary>
	void ChangeSelect(SelectionDirection dir);

	/// <summary>
	/// DrawImGuiの描画
	/// </summary>
	void DrawImGui();


private:

	// Inputクラス
	Input* input_ = nullptr;

	// ステージのセレクト番号
	int selectNum_ = 0;

	//Stickの入力を取得
	Vector2 iLStick_{};
	// デッドゾーン
	const float DZone_ = 0.4f;

	// 操作を行ったかのフラグ
	bool isOperationFunc_ = false;

	// 選択したか
	bool isSelect_ = false;

};

