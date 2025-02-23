#pragma once


class TimeSystem  {

private:

	// シングルトン
	TimeSystem () = default;
	~TimeSystem () = default;
	TimeSystem (const TimeSystem &) = delete;
	TimeSystem & operator=(const TimeSystem &) = delete;
	
public:

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

#pragma region Accessor

	// ゲーム開始からの時間
	float Get_SinceStart()const { return this->timeSinceStart_; }

#pragma endregion




private:

	// ゲーム開始からの時間
	float timeSinceStart_ = 0.0f;

};
