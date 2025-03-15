#include "LuaManager.h"



/// <summary>
/// 指定したLuaスクリプトの読み込み
/// </summary>
void LuaManager::LoadScript(const std::string& rootPath, const std::string& fileName)
{
    std::filesystem::path fullPath = std::filesystem::path("Resources") / rootPath / fileName;
    std::string key = RemoveNameSuffix(fileName);

    if (!std::filesystem::exists(fullPath)) {
        std::cerr << "[Lua Error] Script file not found: " << fullPath << std::endl;
        return;
    }

    if (scripts_.find(key) != scripts_.end()) {
        std::cerr << "[Lua Warning] Script already loaded: " << key << std::endl;
        return;
    }

    auto script = std::make_shared<LuaScript>();
    if (!script->LoadScript(fullPath.string())) {
        std::cerr << "[Lua Error] Failed to load script: " << fullPath << std::endl;
        return;
    }

    scripts_[key] = script;
    scriptPaths_[key] = fullPath;
}


/// <summary>
/// スクリプトのリロード
/// </summary>
void LuaManager::ReLoadScript(const std::string& scriptName)
{
    auto it = scriptPaths_.find(scriptName);
    if (it == scriptPaths_.end()) {
        std::cerr << "Script not found: " << scriptName << std::endl;
        return;
    }

    std::filesystem::path fullPath = it->second;

    auto script = std::make_shared<LuaScript>();
    if (!script->LoadScript(fullPath.string())) {
        std::cerr << "Failed to reload Lua script: " << fullPath << std::endl;
        return;
    }

    scripts_[scriptName] = script;  // 更新
    std::cout << "Reloaded script: " << scriptName << std::endl;
}


/// <summary>
/// 指定したスクリプトを取得
/// </summary>
std::weak_ptr<LuaScript> LuaManager::GetScript(const std::string& scriptName)
{
    try {
        return scripts_.at(scriptName);
    }
    catch (const std::out_of_range&) {
        return std::weak_ptr<LuaScript>();
    }
}


/// <summary>
/// 指定したスクリプトを解放
/// </summary>
void LuaManager::UnLoadScript(const std::string& scriptName)
{
    scripts_.erase(scriptName);
}
