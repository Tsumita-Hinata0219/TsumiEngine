#pragma once

#include "Math/MyMath.h"

#include "../Script/LuaScript.h"


/* Luaスクリプトの管理を一元化するクラス */
class LuaManager {

public:

	/// <summary>
	/// コンストラク
	/// </summary>
	LuaManager() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~LuaManager() = default;

	/// <summary>
	/// 指定したLuaスクリプトの読み込み
	/// </summary>
	std::shared_ptr<LuaScript> LoadScript(const std::string& scriptName, const std::string& fileName);

	/// <summary>
	/// 指定したスクリプトを取得
	/// </summary>
	std::shared_ptr<LuaScript> GetScript(const std::string& scriptName);

	/// <summary>
	/// 指定したスクリプトを解放
	/// </summary>
	void UnLoadScript(const std::string& scriptName);


private:

	std::unordered_map<std::string, std::shared_ptr<LuaScript>> scripts_;

};
