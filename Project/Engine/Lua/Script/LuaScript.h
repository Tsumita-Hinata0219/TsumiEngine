#pragma once

#include <sol/sol.hpp>
#include <memory>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>

#include "Math/MyMath.h"
#include "../Helpers/LuaHelpers.h"


/* 個々のスクリプトを管理するクラス */
class LuaScript {

public:

    using ReloadCallback = std::function<void()>;  // コールバック型定義

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
    void LoadScript(const std::string& rootPath, const std::string& fileName);

    /// <summary>
    /// スクリプトの変更を監視
    /// </summary>
    void MonitorScript();

    /// <summary>
    /// スクリプトの再評価
    /// </summary>
    bool Reload(const std::string& file);

    /// <summary>
    /// リロード時のコールバックの登録
    /// </summary>
    void SetReloadCallBack(ReloadCallback callback);

    /// <summary>
    /// Lua側の変数を取得
    /// </summary>
    /// <typeparam name="T"> 取得変数の型 </typeparam>
    /// <param name="varName"> Lua側にある変数名 </param>
    template <typename T> T GetVariable(const std::string& varName) const; 

    /// <summary>
    /// Lua側の関数を実行
    /// </summary>
    /// <param name="funcName"> Lua側にある関数名 </param>
    /// <param name="...args"> 引数 </param>
    template <typename... Args> bool ExeFunction(const std::string& funcName, Args... args);

    /// <summary>
    /// Lua側の関数を実行し、戻り値を受け取る
    /// </summary>
    template<typename Ret, typename ...Args>
    std::optional<Ret> CallFunction(const std::string& funcName, Args ...args);


private:

    /// <summary>
    /// スクリプトの読み込み＆エラーハンドリング処理
    /// </summary>
    bool LoadFromFile(const std::string& file);


private:

    // ステート
    sol::state lua_;

    // スクリプトのフルパス
    std::filesystem::path fullPath_;
    // 最終更新
    std::filesystem::file_time_type updateTime_;

    // コールバック関数
    ReloadCallback reloadCallback_ = nullptr;
};



/// <summary>
/// コンストラクタ
/// </summary>
inline LuaScript::LuaScript()
{
    lua_.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math);
}


/// <summary>
/// スクリプトの読み込み
/// </summary>
inline void LuaScript::LoadScript(const std::string& rootPath, const std::string& fileName)
{
    fullPath_ = std::filesystem::path("Resources") / rootPath / fileName;

    if (!std::filesystem::exists(fullPath_)) {
        throw std::runtime_error("Lua file not found: " + fullPath_.string());
    }

    sol::load_result result = lua_.load_file(fullPath_.string());
    if (!result.valid()) {
        sol::error err = result;
        std::cerr << "[Lua Error] " << err.what() << std::endl;
        throw std::runtime_error(err.what());
    }

    lua_.script_file(fullPath_.string());  // 実行
    updateTime_ = std::filesystem::last_write_time(fullPath_);
}


/// <summary>
/// スクリプトの変更を監視
/// </summary>
inline void LuaScript::MonitorScript()
{
    // 現在のファイル更新時刻を取得
    auto currentTime = std::filesystem::last_write_time(fullPath_);

    // 以前と異なっていれば変更とみなす
    if (updateTime_ != currentTime) {
        std::cout << "[Lua] Detected change in script: " << fullPath_ << std::endl;

        // スクリプト再読み込み（LoadScriptは更新済みのファイルパスを再利用）
        if (Reload(fullPath_.string())) {
            // 読み込み成功時のみ時刻を更新
            updateTime_ = currentTime;

            // コールバックがあれば呼び出す
            if (reloadCallback_) {
                reloadCallback_();
            }
        }
        else {
            std::cerr << "[Lua Error] Failed to reload script: " << fullPath_ << std::endl;
        }
    }
}


/// <summary>
/// スクリプトの再評価
/// </summary>
inline bool LuaScript::Reload(const std::string& file)
{
    try {
        lua_.script_file(file);
        if (reloadCallback_) reloadCallback_();
        return true;
    }
    catch (const sol::error& e) {
        std::cerr << "[Lua Error] Reload failed: " << e.what() << std::endl;
        return false;
    }
}


/// <summary>
/// リロード時のコールバックの登録
/// </summary>
inline void LuaScript::SetReloadCallBack(ReloadCallback callback)
{
    reloadCallback_ = callback;
}


/// <summary>
/// スクリプトの読み込み＆エラーハンドリング処理
/// </summary>
inline bool LuaScript::LoadFromFile(const std::string& file)
{
    try {
        lua_.script_file(file);
        return true;
    }
    catch (const sol::error& e) {
        std::cerr << "[Lua Error] Failed to load script: " << file << "\n" << e.what() << std::endl;
        return false;
    }
}


/// <summary>
/// Lua側の変数を取得
/// </summary>
template<typename T>
inline T LuaScript::GetVariable(const std::string& varName) const
{
    sol::object obj = lua_[varName];
    if (!obj.valid()) {
        std::cerr << "[Lua Error] Variable not found: " << varName << std::endl;
        return T(); // デフォルト
    }

    return obj.as<T>();
}
// 明示的なインスタンス化
template int LuaScript::GetVariable<int>(const std::string&) const;
template float LuaScript::GetVariable<float>(const std::string&) const;
template bool LuaScript::GetVariable<bool>(const std::string&) const;
template std::string LuaScript::GetVariable<std::string>(const std::string&) const;
template Vector2 LuaScript::GetVariable<Vector2>(const std::string&) const;
template Vector3 LuaScript::GetVariable<Vector3>(const std::string&) const;
template Vector4 LuaScript::GetVariable<Vector4>(const std::string&) const;


/// <summary>
/// Lua側の関数を実行
/// </summary>
/// <param name="funcName"> Lua側にある関数名 </param>
/// <param name="...args"> 引数 </param>
template <typename... Args>
inline bool LuaScript::ExeFunction(const std::string& funcName, Args... args)
{
    sol::function func = lua_[funcName];
    if (!func.valid()) {
        std::cerr << "[Lua Error] Function not found: " << funcName << std::endl;
        return false;
    }

    sol::protected_function_result result = func(args...);
    if (!result.valid()) {
        sol::error err = result;
        std::cerr << "[Lua Error] Function call failed: " << err.what() << std::endl;
        return false;
    }

    return true;
}


/// <summary>
/// Lua側の関数を実行し、戻り値を受け取る
/// </summary>
template<typename Ret, typename ...Args>
inline std::optional<Ret> LuaScript::CallFunction(const std::string& funcName, Args ...args)
{
    sol::function func = lua_[funcName];
    if (!func.valid()) {
        std::cerr << "[Lua Error] Function not found: " << funcName << std::endl;
        return std::nullopt;
    }

    sol::protected_function_result result = func(args...);
    if (!result.valid()) {
        sol::error err = result;
        std::cerr << "[Lua Error] Error calling function " << funcName << ": " << err.what() << std::endl;
        return std::nullopt;
    }

    return result.get<Ret>();
}
