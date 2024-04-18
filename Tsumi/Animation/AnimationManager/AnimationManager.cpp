#include "AnimationManager.h"



// 初期化処理
void AnimationManager::Initialize()
{


}


// 更新処理
void AnimationManager::Update()
{



}


// Animationを読み込む
Animation AnimationManager::LoadAnimationFile(const std::string& routeFilePath, const std::string& fileName)
{
	// 一回読み込んだファイルは読み込まないようにチェックする
	if (CheckAnimationFile(fileName)) {

		// 読み込んだことなかったら読み込み開始
		Animation animation; // 今回作るアニメーションデータ
		Assimp::Importer importer;
		string filePath = routeFilePath + "/" + fileName;
		const aiScene* scene = importer.ReadFile(filePath.c_str(), 0);
		
		assert(scene->mNumAnimations && "アニメーションがない");

		// 最初のアニメーションだけ採用。もちろん複数対応するに越したことはない
		aiAnimation* animationAssimp = scene->mAnimations[0];
		// 時間の単位を秒に変換
		// mTicksPerSecond : 周波数 mDuration : mTickPerSecondで指定された周波数における長さ
		animation.duration = float(animationAssimp->mDuration / animationAssimp->mTicksPerSecond);

		/* --------------------------------------------------------------------------------------
		
		         mTicksPerSecond : 周波数 
				 mDuration : mTickPerSecondで指定された周波数における長さ
		         例えばmTicisPerSecondが1000というのは、1000Hzのことなので、1Tick(周期)は1msである
		         このとき、mDurationが2000なら、2000ms = s2である

		-----------------------------------------------------------------------------------------*/


		// NodeAnimationを解析する
		// assimpでは個々のNodeのAnimationをchannelと読んでるのでchannelを回してNodeAnimationの情報をとってくる
		for (uint32_t channelIndex = 0; channelIndex < animationAssimp->mNumChannels; ++channelIndex) {

			aiNodeAnim* nodeAnimationAssimp = animationAssimp->mChannels[channelIndex];
			NodeAnimation& nodeAnimation = animation.nodeAnimations[nodeAnimationAssimp->mNodeName.C_Str()];
			
			for (uint32_t keyIndex = 0; keyIndex < nodeAnimationAssimp->mNumPositionKeys; ++keyIndex) {

				aiVectorKey& keyAssimp = nodeAnimationAssimp->mPositionKeys[keyIndex];
				KeyFrameVector3 keyFrame{};
				keyFrame.time = float(keyAssimp.mTime / animationAssimp->mTicksPerSecond); // ここも秒に変換
				keyFrame.value = { -keyAssimp.mValue.x, keyAssimp.mValue.y, keyAssimp.mValue.z }; // 右手->左手
				nodeAnimation.translate.keyFrames.push_back(keyFrame);
			}
		}

	}


	// 同じファイル名のデータを返す
	return (*animationDatas_[fileName].get());
}


// 同じファイルは読み込まない
bool AnimationManager::CheckAnimationFile(string fileName)
{
	if (animationDatas_.find(fileName) == animationDatas_.end()) {
		return true;
	}

	return false;
}
