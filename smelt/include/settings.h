#pragma once
#include <string>

namespace smelt
{
    struct Settings
    {
        bool Quiet;
		std::string CompileTarget;
		std::string ProjectPath;
    };
}