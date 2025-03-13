#include "LuaScript.h"



/// <summary>
/// コンストラク
/// </summary>
LuaScript::LuaScript() : L_(luaL_newstate(), &lua_close)
{
    luaL_openlibs(L.get());  // Luaライブラリを開く
}

/// <summary>
/// スクリプトの読み込み
/// </summary>
bool LuaScript::LoadScript(const string& file)
{
    if (luaL_dofile(L_.get(), file.c_str()) != LUA_OK) {
        std::cerr << "Error loading Lua script: " << lua_tostring(L_.get(), -1) << std::endl;
        return false;
    }
    return true;
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
/// Lua側の変数を取得
/// </summary>
int LuaScript::GetInt(const std::string& varName)
{
    varName;
    return 0;
}
float LuaScript::GetFloat(const std::string& varName)
{
    varName;
    return 0;
}
bool LuaScript::GetBool(const std::string& varName)
{
    varName;
    return 0;
}
std::string LuaScript::GetString(const std::string& varName)
{
    varName;
    return "";
}

