#include "LuaManager.h"

//
//
///// <summary>
///// 指定したLuaスクリプトの読み込み
///// </summary>
//void LuaManager::LoadScript(const std::string& rootPath, const std::string& fileName)
//{
//    std::filesystem::path fullPath = rootPath + fileName;
//
//    // すでにロード済みならスキップ
//    if (scripts_.find(fileName) != scripts_.end()) {
//        std::cerr << "Warning: Script already loaded: " << fileName << std::endl;
//        return;
//    }
//
//    // 新しいスクリプトを読み込む
//    std::shared_ptr<LuaScript> script = std::make_shared<LuaScript>();
//    if (!script->LoadScript(fullPath.string())) {
//        std::cerr << "Error: Failed to load script: " << fullPath << std::endl;
//        return;
//    }
//
//    // マップに登録
//    scripts_[fileName] = script;
//    scriptPaths_[fileName] = fullPath;
//}
//
//
///// <summary>
///// スクリプトのリロード
///// </summary>
//void LuaManager::ReLoadScript(const std::string& scriptName)
//{
//    auto it = scriptPaths_.find(scriptName);
//    if (it == scriptPaths_.end()) {
//        std::cerr << "Script not found: " << scriptName << std::endl;
//        return;
//    }
//
//    std::filesystem::path fullPath = it->second;
//
//    auto script = std::make_shared<LuaScript>();
//    if (!script->LoadScript(fullPath.string())) {
//        std::cerr << "Failed to reload Lua script: " << fullPath << std::endl;
//        return;
//    }
//
//    scripts_[scriptName] = script;  // 更新
//    std::cout << "Reloaded script: " << scriptName << std::endl;
//}
//
//
///// <summary>
///// 指定したスクリプトを取得
///// </summary>
//std::weak_ptr<LuaScript> LuaManager::GetScript(const std::string& scriptName)
//{
//    if (scripts_.find(scriptName) != scripts_.end()) {
//        return scripts_[scriptName];
//    }
//
//    // 存在しない場合は empty weal_ptr を返す
//    return std::weak_ptr<LuaScript>();
//}
//
//
///// <summary>
///// 指定したスクリプトを解放
///// </summary>
//void LuaManager::UnLoadScript(const std::string& scriptName)
//{
//    scripts_.erase(scriptName);
//}
