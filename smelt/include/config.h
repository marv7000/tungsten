#pragma once
#include <unordered_map>
#include <vector>
#include <string>

#include "shared.h"

namespace smelt
{
    using Properties = std::unordered_map<std::string, std::vector<std::string>>;

    class Config
    {
        Properties mProps{};
    public:
        Config(const std::string& path);
        const std::string& GetString(const std::string& key);
        const std::vector<std::string>& GetStringArray(const std::string& key);
        i64 GetNum(const std::string& key);
    };
}