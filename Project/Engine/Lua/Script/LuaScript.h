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
	LuaScript();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~LuaScript() = default;

	/// <summary>
	/// スクリプトの読み込み
	/// </summary>
	bool LoadScript(const string& file);

	/// <summary>
	/// Lua側の関数を実行
	/// </summary>
	template <typename... Args>
	bool ExeFunction(const std::string& funcName, Args... args);

	/// <summary>
	/// Lua側の変数を取得
	/// </summary>
	template <typename T>
	T GetVariable(const std::string& varName);


private:

	/// <summary>
	/// 可変引数を Lua にプッシュする
	/// </summary>
	void PushToLua(int value);
	void PushToLua(float value);
	void PushToLua(double value);
	void PushToLua(const std::string& value);
	void PushToLua(const Vector2& value);
	void PushToLua(const Vector3& value);
	void PushToLua(const Vector4& value);


private:

	std::unique_ptr<lua_State, decltype(&lua_close)> L_;

};

