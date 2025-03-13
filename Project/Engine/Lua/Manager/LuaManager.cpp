#include "LuaManager.h"



/// <summary>
/// 指定したLuaスクリプトの読み込み
/// </summary>
void LuaManager::LoadScript(const std::string& rootPath, const std::string& fileName)
{
    // 1. スクリプトファイルのフルパスを組み立てる
    std::filesystem::path fullPath = std::filesystem::path(rootPath) / fileName;

    if (!std::filesystem::exists(fullPath)) {
        std::cerr << "Error: Script file does not exist: " << fullPath << std::endl;
        return;
    }

    // 2. Luaスクリプトのインスタンスを作成
    auto script = std::make_shared<LuaScript>();
    if (script->LoadScript(fullPath.string())) {
        // 3. スクリプトをマップに登録
        scripts_[fileName] = script;
        std::cout << "Loaded script: " << fullPath << std::endl;
    }
    else {
        std::cerr << "Failed to load script: " << fullPath << std::endl;
    }
}


/// <summary>
/// 指定したスクリプトを取得
/// </summary>
std::weak_ptr<LuaScript> LuaManager::GetScript(const std::string& scriptName)
{
    if (scripts_.find(scriptName) != scripts_.end()) {
        return scripts_[scriptName];
    }

    // 存在しない場合は empty weal_ptr を返す
    return std::weak_ptr<LuaScript>();
}


/// <summary>
/// 指定したスクリプトを解放
/// </summary>
void LuaManager::UnLoadScript(const std::string& scriptName)
{
    scripts_.erase(scriptName);
}
