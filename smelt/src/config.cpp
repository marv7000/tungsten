#include "config.h"
#include <fstream>
#include <iostream>

namespace smelt
{
    Config::Config(const std::string& path)
    {
        std::ifstream f(path);
        if (f.bad()) 
        {
            std::cerr << "ERROR: File " << path << " not found in this directory!\n";
            std::exit(-1);
        }

        std::string line;
        while (std::getline(f, line))
        {
            // Seek to the start of the block.
            if (line == "") continue;
            // Until an empty line is hit, count the first line as the key and the rest as value.
            std::string key = line;
            while (std::getline(f, line))
            {
                if (line.empty())
                {
                    break;
                }
                mProps[key].push_back(line);
            }
        }
    }

    const std::string& Config::GetString(const std::string& key)
    {
        auto& arr = GetStringArray(key);
        if (arr.size() == 0)
        {
            std::cerr << "ERROR:\n\tParameter \"" << key << "\" has no value!\n"; 
            exit(-1);
        }
        else if (arr.size() > 1)
        {
            std::cerr << "ERROR:\n\tParameter \"" << key << "\" has more than one value!\n"; 
            exit(-1);
        }

        return arr[0];
    }

    const std::vector<std::string>& Config::GetStringArray(const std::string& key)
    {
        if (!mProps.contains(key)) 
        { 
            std::cerr << "ERROR:\n\tConfig file is missing parameter \"" << key << "\"!\n"; 
            exit(-1);
        } 
        return mProps[key];
    }

    i64 Config::GetNum(const std::string &key)
    {
        auto& s = GetString(key);
        return std::stoll(s);
    }
}