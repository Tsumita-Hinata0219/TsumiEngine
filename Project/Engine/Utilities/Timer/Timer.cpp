#include "Timer.h"



// タイマーの設定
void Timer::Init(float setStart, float setEnd)
{
	nowFrame_ = setStart;
	endFrame_ = setEnd;

	saveTimer_ = { setStart, setEnd };

	frameRatio_ = nowFrame_ / endFrame_;

	isActive_ = true;
	isFinish_ = false;
}

// スタート時に呼び出す処理
void Timer::Start()
{
	// 既にスタートしていたら早期return
	if (isActive_) {
		return;
	}

	isActive_ = true;
	isFinish_ = false;
}


// タイマーの更新処理
void Timer::Update(bool roop)
{
	if (isFinish_) {
		if (roop) {
			this->Init(saveTimer_.first, saveTimer_.second);
			this->Start();
			return;
		}
		isActive_ = false;
		return;
	}

	nowFrame_++;
	frameRatio_ = nowFrame_ / endFrame_;

	if (nowFrame_ >= endFrame_) {
		isActive_ = false;
		isFinish_ = true;
	}
}


// リセット
void Timer::Reset()
{
	nowFrame_ = saveTimer_.first;
	endFrame_ = saveTimer_.second;
	isActive_ = false;
	isFinish_ = true;
}


// クリア
void Timer::Clear()
{
	nowFrame_ = 0;
	endFrame_ = 0;
	frameRatio_ = 0.0f;
	isActive_ = false;
	isFinish_ = true;
}
