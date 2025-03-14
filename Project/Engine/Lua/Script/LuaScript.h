#pragma once

#include <iostream>
#include <lua.hpp>

#include "Math/MyMath.h"


/* 個々のスクリプトを管理するクラス */
class LuaScript {

public:

	/// <summary>
	/// コンストラク
	/// </summary>
	//LuaScript();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~LuaScript() = default;

	/// <summary>
	/// スクリプトの読み込み
	/// </summary>
	//bool LoadScript(const string& file);

//	/// <summary>
//	/// Lua側の関数を実行
//	/// </summary>
//	bool ExeFunction(const string& funcName, int arg = 0);
//
//	/// <summary>
//	/// Lua側の変数を取得
//	/// </summary>
//	int GetInt(const std::string& varName);
//	float GetFloat(const std::string& varName);
//	bool GetBool(const std::string& varName);
//	std::string GetString(const std::string& varName);
//	template <typename T>
//	T GetVariable(const std::string& varName);


private:

	std::unique_ptr<lua_State, decltype(&lua_close)> L_;

};

