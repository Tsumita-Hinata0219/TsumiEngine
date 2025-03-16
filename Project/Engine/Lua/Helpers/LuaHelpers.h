#pragma once


#include <iostream>
#include <lua.hpp>

#include "Math/MyMath.h"


// --- ヘルパー関数：Luaスタックへ値をプッシュ ---
// int, float, double, std::string, const char* に対応
inline void PushValue(lua_State* L, int value) {
    lua_pushinteger(L, value);
}
inline void PushValue(lua_State* L, float value) {
    lua_pushnumber(L, value);
}
inline void PushValue(lua_State* L, double value) {
    lua_pushnumber(L, value);
}
inline void PushValue(lua_State* L, const std::string& value) {
    lua_pushstring(L, value.c_str());
}
inline void PushValue(lua_State* L, const char* value) {
    lua_pushstring(L, value);
}
// 例：Vector3型の場合（必要に応じてVector2, Vector4も定義）
inline void PushValue(lua_State* L, const Vector3& value) {
    lua_newtable(L);                     // 新しいテーブルを作成
    lua_pushnumber(L, value.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, value.y);
    lua_setfield(L, -2, "y");
    lua_pushnumber(L, value.z);
    lua_setfield(L, -2, "z");
}

// --- 可変引数を一括でプッシュするための再帰テンプレート関数 ---
template <typename T>
void PushAll(lua_State* L, T value) {
    PushValue(L, value);
}
template <typename T, typename... Args>
void PushAll(lua_State* L, T value, Args... args) {
    PushValue(L, value);
    PushAll(L, args...);
}