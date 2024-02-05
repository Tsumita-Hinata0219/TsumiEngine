#include "EngineManual.h"



/// <summary>
/// デストラクタ
/// </summary>
EngineManual::~EngineManual() 
{


}


/// <summary>
/// 初期化処理
/// </summary>
void EngineManual::Initialize() 
{
	// 雲模様背景
	cloudBG_ = make_unique<Cloud>();
	cloudBG_->Initialize();

	// モンスターボール
	monsBall_ = make_unique<MonsBall>();
	monsBall_->Initialize();

	// 光子パーティクル
	photon_ = make_unique<Photon>();
	photon_->Initialize();
}


/// <summary>
/// 更新処理
/// </summary>
void EngineManual::Update(ViewProjection view) 
{
	// 雲模様背景
	cloudBG_->Update();

	// モンスターボール
	monsBall_->Update();

	// 光子パーティクル
	photon_->Update();

#ifdef _DEBUG


#endif // _DEBUG

}


/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void EngineManual::BackSpriteDraw(ViewProjection view) 
{
	// 雲模様背景
	cloudBG_->Draw(view);

}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void EngineManual::ModelDraw(ViewProjection view) 
{
	// モンスターボール
	monsBall_->Draw(view);

	// 光子パーティクル
	photon_->Draw(view);
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void EngineManual::FrontSpriteDraw(ViewProjection view) 
{


}


/// <summary>
/// Audioに関する処理まとめたやつ
/// </summary>
void EngineManual::AudioUpdate() 
{



#ifdef _DEBUG



#endif // _DEBUG
}