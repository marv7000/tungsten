#pragma once
#include "settings.h"
#include <vector>
#include <string>

#define SM_PROJECT_FILE "project.txt"
#define SM_PROJECT_NAME "Name"
#define SM_PROJECT_VERSION "Version"


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

        std::string mName;
        std::string mVersion;
        ProjectType mType;
        std::vector<std::string> mDependencies;

    public:
        Project(Settings* settings);
    };
}
