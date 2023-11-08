#include "project.h"
#include "config.h"
#include "parser.h"
#include "lexer.h"

#include <cassert>
#include <iostream>

namespace smelt
{
    Project::Project(Settings* settings)
    {
        assert(settings);
        mSettings = settings;

        // Parse the main project file.
        auto p = Config(mSettings->ProjectPath + "project.txt");

        // Assign properties from the config file.
        mName = p.GetString("Name");
        mVersion = p.GetString("Version");

        // Parse project type.
        auto& projectType = p.GetString("Type");
        if (projectType == "Application") mType = ProjectType::Application;
        else if (projectType == "Library") mType = ProjectType::Library;

        mDependencies = p.GetStringArray("Dependencies");

		// Check all dependencies and add every Tungsten file we can find.
		for (auto& dep : mDependencies)
		{
			for (auto& pa : std::filesystem::recursive_directory_iterator(dep))
			{
				if (pa.path().extension() != SM_FILE_ENDING)
					continue;

				mFiles.push_back(pa.path());
			}
		}
    }

	void Project::Compile()
	{
		// For each file.
		for (auto& file : mFiles)
		{
			// Tokenize the file.
			auto* lexer = new Lexer(file);
			auto* parser = new Parser(lexer);

			// Clean up.
			delete lexer;
			delete parser;
		}
	}
}
