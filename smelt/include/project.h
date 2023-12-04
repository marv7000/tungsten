#pragma once
#include "settings.h"

#include <vector>
#include <string>
#include <filesystem>

#define SM_FILE_ENDING ".tg"

namespace smelt
{
    enum class ProjectType
    {
        Application,
        Library
    };

    /// \brief  Manages a user's project file structure, including external dependencies, compiler flags, etc.
    class Project
    {
        Settings* mSettings;
	public:
        std::string mName;
        std::string mVersion;
        ProjectType mType;
        std::vector<std::string> mDependencies;
		std::vector<std::filesystem::path> mFiles;
		static inline std::string IntermediatePath;

    public:
        explicit Project(Settings* settings);

		void Compile();
    };
}
