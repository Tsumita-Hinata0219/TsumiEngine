#include "LuaScript.h"



/// <summary>
/// コンストラク
/// </summary>
//LuaScript::LuaScript() : L_(luaL_newstate(), &lua_close)
//{
//    luaL_openlibs(L_.get());  // Luaライブラリを開く
//}


/// <summary>
/// スクリプトの読み込み
/// </summary>
//bool LuaScript::LoadScript(const string& file)
//{
//    if (luaL_dofile(L_.get(), file.c_str()) != LUA_OK) {
//        std::cerr << "Error loading Lua script: " << lua_tostring(L_.get(), -1) << std::endl;
//        return false;
//    }
//    return true;
//}


///// <summary>
///// Lua側の関数を実行
///// </summary>
//bool LuaScript::ExeFunction(const string& funcName, int arg)
//{
//    funcName; arg;
//
//    return false;
//}
//
//
///// <summary>
///// Lua側の変数を取得
///// </summary>
//int LuaScript::GetInt(const std::string& varName)
//{
//    varName;
//    return 0;
//}
//float LuaScript::GetFloat(const std::string& varName)
//{
//    varName;
//    return 0;
//}
//bool LuaScript::GetBool(const std::string& varName)
//{
//    varName;
//    return 0;
//}
//std::string LuaScript::GetString(const std::string& varName)
//{
//    varName;
//    return "";
//}
//

//// テンプレート関数の実装
//template <typename T>
//T LuaScript::GetVariable(const std::string& varName) {
//    lua_getglobal(L_.get(), varName.c_str());  // Luaのグローバル変数をスタックにプッシュ
//
//    // 型による処理を分ける
//    if constexpr (std::is_same<T, int>::value) {
//        if (lua_isnumber(L_.get(), -1)) {
//            int value = static_cast<int>(lua_tointeger(L_.get(), -1));
//            lua_pop(L_.get(), 1);
//            return value;
//        }
//    }
//    else if constexpr (std::is_same<T, float>::value) {
//        if (lua_isnumber(L_.get(), -1)) {
//            float value = static_cast<float>(lua_tonumber(L_.get(), -1));
//            lua_pop(L_.get(), 1);
//            return value;
//        }
//    }
//    else if constexpr (std::is_same<T, bool>::value) {
//        if (lua_isboolean(L_.get(), -1)) {
//            bool value = lua_toboolean(L_.get(), -1);
//            lua_pop(L_.get(), 1);
//            return value;
//        }
//    }
//    else if constexpr (std::is_same<T, std::string>::value) {
//        if (lua_isstring(L_.get(), -1)) {
//            std::string value = lua_tostring(L_.get(), -1);
//            lua_pop(L_.get(), 1);
//            return value;
//        }
//    }
//
//    lua_pop(L_.get(), 1);  // 失敗した場合はスタックをポップ
//    return T();  // デフォルト値を返す
//}
//
//// 明示的なインスタンス化
//template int LuaScript::GetVariable<int>(const std::string&);
//template float LuaScript::GetVariable<float>(const std::string&);
//template bool LuaScript::GetVariable<bool>(const std::string&);
//template std::string LuaScript::GetVariable<std::string>(const std::string&);