#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <../externals/json/json.hpp>

/* フラグ管理クラス */
class FlagManager {

public:

    using FlagType = uint32_t;

    /// <summary>
    /// コンストラクタ
    /// </summary>
    FlagManager();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~FlagManager() = default;

    /// <summary>
    /// JSONファイルからフラグ定義をロードする。
    /// </summary>
    void LoadFlagsFromFile(const std::string& filename);

    /// <summary>
    /// 単純フラグ (ON/OFF) の操作
    /// </summary>
    void SetFlag(const std::string& flagName);
    void ClearFlag(const std::string& flagName);
    bool IsFlagSet(const std::string& flagName) const;

    /// <summary>
    /// カウントフラグの操作
    /// </summary>
    void IncrementCountFlag(const std::string& flagName);
    void DecrementCountFlag(const std::string& flagName);
    bool IsCountFlagSet(const std::string& flagName) const;

    /// <summary>
    /// 全フラグのリセット
    /// </summary>
    void Reset();

    /// <summary>
    /// デバッグ用：現在の単純フラグ状態を取得
    /// </summary>
    /// <returns></returns>
    FlagType GetFlagState() const;

    /// <summary>
    /// デバッグ用：カウントフラグの現在の値を取得
    /// </summary>
    int GetCountFlagValue(const std::string& flagName) const;

private:

    // 単純なビットフラグの状態 (ビットマスク)
    FlagType flagState_;

    // 単純フラグ名 -> ビット値
    std::unordered_map<std::string, FlagType> flagMapping_;
    // カウント型フラグ: フラグ名 -> カウント
    std::unordered_map<std::string, int> countFlags_; 
};
