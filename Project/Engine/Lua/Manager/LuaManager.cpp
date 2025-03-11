#include "LuaManager.h"



/// <summary>
/// 指定したLuaスクリプトの読み込み
/// </summary>
std::shared_ptr<LuaScript> LuaManager::LoadScript(const std::string& scriptName, const std::string& fileName)
{
    scriptName; fileName;

    return std::shared_ptr<LuaScript>();
}


/// <summary>
/// 指定したスクリプトを取得
/// </summary>
std::shared_ptr<LuaScript> LuaManager::GetScript(const std::string& scriptName)
{
    scriptName;

    return std::shared_ptr<LuaScript>();
}


/// <summary>
/// 指定したスクリプトを解放
/// </summary>
void LuaManager::UnLoadScript(const std::string& scriptName)
{
    scriptName;
}
