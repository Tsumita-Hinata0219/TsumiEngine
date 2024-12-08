#pragma once



/* シーンをまたいで使用したい値を保存しておくクラス */
class GameData {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameData() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameData() = default;

#pragma region SelectStageNumber

	int Get_StageSelectNum() const { return this->stageSelectNum_; }
	void Set_StageSelectNum(int setNum) { this->stageSelectNum_ = setNum; }
	void NextStageSet() { this->stageSelectNum_++; }

#pragma endregion


private:	

	int stageSelectNum_ = 0;

};
