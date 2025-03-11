#include "LuaScript.h"



/// <summary>
/// スクリプトの読み込み
/// </summary>
bool LuaScript::LoadScript(const string& fileName)
{
    fileName;

    return false;
}


/// <summary>
/// Lua側の関数を実行
/// </summary>
bool LuaScript::ExeFunction(const string& funcName, int arg)
{
    funcName; arg;

    return false;
}


/// <summary>
/// Lua側の数値変数を取得
/// </summary>
float LuaScript::GetNumber(const std::string& verName)
{
    verName;

    return 0.0f;
}


/// <summary>
/// Lua側の文字列変数を取得
/// </summary>
std::string LuaScript::GetString(const std::string& verName)
{
    verName;

    return std::string();
}


/// <summary>
/// Luaステートを閉じる(メモリ解放)
/// </summary>
void LuaScript::Close()
{
}
