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
    /// テキストバッファの再評価
    /// </summary>
    bool ReloadFromBuffer();

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

    /// <summary>
    /// Luaエディタウィンドウを表示します。
    /// </summary>
    void ShowLuaEditorWindow();

private:

    /// <summary>
    /// テキストを読み込む関数
    /// </summary>
    void LoadFileToBuffer(const std::string& path);

    /// <summary>
    /// ファイル保存用関数
    /// </summary>
    void SaveBufferToFile();

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

    // スクリプトテキストをImGui編集用に保持
    char luaBuffer_[8192] = {};
    bool hasUnsavedChanges_ = false;
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

    // スクリプトをロードして、すぐに実行
    sol::load_result result = lua_.load_file(fullPath_.string());
    if (!result.valid()) {
        sol::error err = result;
        std::cerr << "[Lua Error] " << err.what() << std::endl;
        throw std::runtime_error(err.what());
    }

    // 実行する
    result();

    updateTime_ = std::filesystem::last_write_time(fullPath_);

    LoadFileToBuffer(fullPath_.string());
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
    LoadFileToBuffer(file);
    return ReloadFromBuffer();
}


/// <summary>
/// テキストバッファの再評価
/// </summary>
inline bool LuaScript::ReloadFromBuffer()
{
    try {
        sol::load_result result = lua_.load(luaBuffer_);
        if (!result.valid()) {
            sol::error err = result;
            std::cerr << "[Lua Error] Lua code compile error: " << err.what() << std::endl;
            return false;
        }
        result(); // 実行（関数定義や変数設定が有効になる）
        if (reloadCallback_) reloadCallback_();
        std::cout << "[Lua] Reloaded from buffer." << std::endl;
        return true;
    }
    catch (const sol::error& e) {
        std::cerr << "[Lua Error] ReloadFromBuffer failed: " << e.what() << std::endl;
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
/// Luaエディタウィンドウを表示します。
/// </summary>
inline void LuaScript::ShowLuaEditorWindow()
{
    ImGui::Begin("Lua Script Editor");

    if (ImGui::InputTextMultiline("##LuaScript", luaBuffer_, sizeof(luaBuffer_),
        ImVec2(700, 500))) {
        hasUnsavedChanges_ = true;
    }

    if (ImGui::Button("Save")) {
        SaveBufferToFile();
    }
    ImGui::SameLine();
    if (ImGui::Button("Reload")) {
        ReloadFromBuffer();
    }
    ImGui::SameLine();
    if (hasUnsavedChanges_) {
        ImGui::TextColored(ImVec4(1, 0.4f, 0.4f, 1.0f), "*Unsaved changes");
    }

    ImGui::End();
}


/// <summary>
/// テキストを読み込む関数
/// </summary>
inline void LuaScript::LoadFileToBuffer(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "[Lua Error] Failed to open file: " << path << std::endl;
        return;
    }
    std::string content((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());
    memset(luaBuffer_, 0, sizeof(luaBuffer_));
    strncpy(luaBuffer_, content.c_str(), sizeof(luaBuffer_) - 1);
    hasUnsavedChanges_ = false;
}


/// <summary>
/// ファイル保存用関数
/// </summary>
inline void LuaScript::SaveBufferToFile()
{
    if (!hasUnsavedChanges_) return;
    std::ofstream file(fullPath_);
    if (!file.is_open()) {
        std::cerr << "[Lua Error] Failed to save file: " << fullPath_ << std::endl;
        return;
    }
    file << luaBuffer_;
    file.close();
    hasUnsavedChanges_ = false;
    std::cout << "[Lua] Script saved: " << fullPath_ << std::endl;
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
    sol::object obj;
    sol::table current = lua_.globals();
    std::istringstream ss(varName);
    std::string token;

    while (std::getline(ss, token, '.')) {
        std::cout << "[Debug] token = '" << token << "'" << std::endl;

        obj = current[token];

        if (!obj.valid()) {
            std::cerr << "[Lua Error] Variable part not found: " << token << std::endl;
            return T(); // ここで無効な場合は即終了
        }

        if (obj.is<sol::table>()) {
            current = obj.as<sol::table>();  // テーブルならcurrentを更新
            std::cout << "[Debug] token is table, updating current table" << std::endl;
        }
        else if (ss.peek() != EOF) {
            std::cerr << "[Lua Error] Intermediate token is not a table: " << token << std::endl;
            return T();
        }
    }

    try {
        if constexpr (std::is_same_v<T, Vector4>) {
            return LuaTableToVector4(obj.as<sol::table>());
        }
        else if constexpr (std::is_same_v<T, Vector3>) {
            return LuaTableToVector3(obj.as<sol::table>());
        }
        else if constexpr (std::is_same_v<T, Vector2>) {
            return LuaTableToVector2(obj.as<sol::table>());
        }
        else {
            return obj.as<T>();
        }
    }
    catch (const sol::error& e) {
        std::cerr << "[Lua Error] Failed to convert '" << varName << "' : " << e.what() << std::endl;
        return T();
    }
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