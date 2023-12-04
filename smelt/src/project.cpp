#include "project.h"
#include "config.h"
#include "parser.h"
#include "lexer.h"
#include "code.h"

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
			std::filesystem::path path = std::filesystem::path(settings->ProjectPath);
			path += std::filesystem::path(dep);
			for (auto& pa : std::filesystem::recursive_directory_iterator(path))
			{
				if (pa.path().extension() != SM_FILE_ENDING)
					continue;

				mFiles.push_back(canonical(pa.path()));
			}
		}
    }

	void Project::Compile()
	{
		auto p = std::filesystem::path(mSettings->ProjectPath + "/out/");

		if (std::filesystem::is_directory(p) || std::filesystem::exists(p))
		{
			std::filesystem::remove_all(p);
		}
		std::filesystem::create_directory(p);
		IntermediatePath = p.replace_filename(mName + ".ll");

		// For each file.
		for (auto& file : mFiles)
		{
			// Tokenize the file.
			auto* lexer = new Lexer(file);
			auto* parser = new Parser(lexer);
			parser->Parse();
			// Clean up.
			delete lexer;
			delete parser;
		}
	}
}
