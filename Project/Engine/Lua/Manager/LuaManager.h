#pragma once

#include "Math/MyMath.h"

#include "../Script/LuaScript.h"


/* Luaスクリプトの管理を一元化するクラス */
class LuaManager {

private:

	// コンストラク、デストラクタ
	LuaManager() = default;
	~LuaManager() = default;
	LuaManager(const LuaManager&) = delete;
	const LuaManager& operator=(const LuaManager&) = delete;


public:

	/// <summary>
	/// インスタンス取得
	/// </summary>
	static LuaManager* GetInstance() {
		static LuaManager instance;
		return &instance;
	}

	///// <summary>
	///// 指定したLuaスクリプトの読み込み
	///// </summary>
	//void LoadScript(const std::string& rootPath, const std::string& fileName);

	///// <summary>
	///// スクリプトのリロード
	///// </summary>
	//void ReLoadScript(const std::string& scriptName);

	///// <summary>
	///// 指定したスクリプトを取得
	///// </summary>
	//std::weak_ptr<LuaScript> GetScript(const std::string& scriptName);

	///// <summary>
	///// 指定したスクリプトを解放
	///// </summary>
	//void UnLoadScript(const std::string& scriptName);


private:

	std::unordered_map<std::string, std::shared_ptr<LuaScript>> scripts_;
	std::unordered_map<std::string, std::filesystem::path> scriptPaths_;

};
