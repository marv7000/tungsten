#include "project.h"
#include "shared.h"
#include "config.h"

#include <cassert>
#include <iostream>
#include <fstream>

namespace smelt
{
    Project::Project(Settings* settings)
    {
        std::cout << SM_PREFIX "Loading project...\n";

        assert(settings);
        mSettings = settings;

        // Parse the main project file.
        auto p = Config(SM_PROJECT_FILE);

        // Assign properties from the config file.
        mName = p.GetString("Name");
        mVersion = p.GetString("Version");

        // Parse project type.
        auto& projectType = p.GetString("Type");
        if (projectType == "Application") mType = ProjectType::Application;
        else if (projectType == "Library") mType = ProjectType::Library;

        mDependencies = p.GetStringArray("Dependencies");

        for (auto& dep : mDependencies)
            std::cout << dep << "\n";
    }
}