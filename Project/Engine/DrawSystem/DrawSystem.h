#pragma once

#include "Base/DXCommon/DirectXCommon.h"
#include "CommandManager/CommandManager.h"
#include "PipeLineManager/PipeLineManager.h"
#include "CreateResource/CreateResource.h"
#include "DescriptorManager/DescriptorManager.h"
#include "Math/MyMath.h"
#include "Math/Struct.h"
#include "GameObject/Camera/Manager/CameraManager.h"
#include "CollisionSystem/Structure/CollisionStructures.h"


/* DrawSyetemクラス */
class DrawSystem {

public: // メンバ関数

	DrawSystem() {};
	~DrawSystem() {};

	/// <summary>
	/// インスタンス取得
	/// </summary>
	static DrawSystem* GetInstance();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 描画処理
	/// </summary>
	static void Line(Segment segment, Vector4 color = { 1.0f, 1.0f, 1.0f, 1.0f });


private: // メンバ関数

	/// <summary>
	/// コマンドコール
	/// </summary>
	void CommandCallTypeLine();

private: // メンバ変数

	// リソース
	ResourcePeroperty lineResource_{};
};

