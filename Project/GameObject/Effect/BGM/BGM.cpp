#include "BGM.h"



// デストラクタ
BGM::~BGM()
{
	Audio::SoundUnload();
}

// 初期化処理
void BGM::Initialize()
{
	// サウンドの読み込み
	kakkoiiAudioHD_ = Audio::LoadSound("kakkoii.wav");

	// ボリューム
	volume_ = 0.5f;

	// 再生中か
	AudioIsPlaying_ = Audio::IsPlaying(kakkoiiAudioHD_);

	// テクスチャの読み込み
	AudioTexHD_ = TextureManager::LoadTexture("Audio.png");
	isStateTexHD_[0] = TextureManager::LoadTexture("isPlay.png");
	isStateTexHD_[1] = TextureManager::LoadTexture("isStop.png");
	volumeTexHD_ = TextureManager::LoadTexture("volume.png");

	// スプライト
	AudioS_ = make_unique<Sprite>();
	AudioS_->Initialize(Vector2::zero, { 256.0f, 128.0f });
	AudioWt_.Initialize();
	AudioWt_.translate = { 50.0f, 592.0f, 0.0f };
	AudioWt_.translate /= 2.0f;

	for (int i = 0; i < 2; ++i) {
		isStateS_[i] = make_unique<Sprite>();
		isStateS_[i]->Initialize(Vector2::zero, { 256.0f, 128.0f });
		isStateWt_[i].Initialize();
		isStateWt_[i].translate = { 315.0f, 592.0f, 0.0f };
		isStateWt_[i].translate /= 2.0f;
	}

	volumeS_ = make_unique<Sprite>();
	volumeS_->Initialize(Vector2::zero, { 256.0f, 128.0f });
	volumeWt_.Initialize();
	volumeWt_.translate = { 600.0f, 592.0f, 0.0f };
	volumeWt_.translate /= 2.0f;
}


// 更新処理
void BGM::Update()
{
	// ワールドトランスフォームの更新
	AudioWt_.UpdateMatrix();
	for (int i = 0; i < 2; ++i) {
		isStateWt_[i].UpdateMatrix();
	}
	volumeWt_.UpdateMatrix();
	

	// 再生中か
	AudioIsPlaying_ = Audio::IsPlaying(kakkoiiAudioHD_);

	if (KeysInput::TriggerKey(DIK_SPACE)) {

		// 再生中か
		if (!Audio::IsPlaying(kakkoiiAudioHD_)) {
			Audio::PlayOnSound(kakkoiiAudioHD_, false, volume_);
		}
		else {
			Audio::StopOnSound(kakkoiiAudioHD_);
		}
	}
	// 再生中
	if (Audio::IsPlaying(kakkoiiAudioHD_)) {

		// 音量を上げる
		if (KeysInput::TriggerKey(DIK_UP)) {

			if (volume_ >= 1.0f) {
				volume_ = 1.0f;
				return;
			}
			volume_ += 0.1f;
		}

		// 音量を下げる
		if (KeysInput::TriggerKey(DIK_DOWN)) {

			if (volume_ <= 0.0f) {
				volume_ = 0.0f;
				return;
			}
			volume_ -= 0.1f;
		}

		// ボリュームの設定
		Audio::SetSoundVolum(kakkoiiAudioHD_, volume_);
	}


	if (ImGui::TreeNode("Audio")) {

		ImGui::Checkbox("Audio_IsPlaying", &AudioIsPlaying_);
		ImGui::Text("Volume = % .2f", volume_);
		ImGui::DragFloat2("AudioS_Translate", &AudioWt_.translate.x, 0.1f);
		ImGui::TreePop();
	}
}


// 描画処理
void BGM::Draw(ViewProjection view)
{
	AudioS_->Draw(AudioTexHD_, AudioWt_, view);
	
	if (Audio::IsPlaying(kakkoiiAudioHD_)) {
		isStateS_[0]->Draw(isStateTexHD_[0], isStateWt_[0], view);
	}
	else {
		isStateS_[1]->Draw(isStateTexHD_[1], isStateWt_[1], view);
	}

	volumeS_->Draw(volumeTexHD_, volumeWt_, view);
}
