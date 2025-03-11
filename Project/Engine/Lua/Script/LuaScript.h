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
	LuaScript() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~LuaScript() = default;

	/// <summary>
	/// スクリプトの読み込み
	/// </summary>
	bool LoadScript(const string& fileName);

	/// <summary>
	/// Lua側の関数を実行
	/// </summary>
	bool ExeFunction(const string& funcName, int arg = 0);

	/// <summary>
	/// Lua側の数値変数を取得
	/// </summary>
	float GetNumber(const std::string& verName);

	/// <summary>
	/// Lua側の文字列変数を取得
	/// </summary>
	std::string GetString(const std::string& verName);

	/// <summary>
	/// Luaステートを閉じる(メモリ解放)
	/// </summary>
	void Close();


private:

};
