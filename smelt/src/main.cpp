#include <iostream>
#include <filesystem>

#include "llvm/TargetParser/Host.h"

#include "shared.h"
#include "project.h"
#include "settings.h"
#include <llvm/TargetParser/Host.h>

using namespace smelt;

i32 main(const i32 argc, const i8** argv)
{
#pragma region Settings
	// Parse arguments and settings.
	auto* settings = new Settings();

	// Defaults.
	settings->Quiet = false;
	settings->CompileTarget = llvm::sys::getDefaultTargetTriple();
	settings->ProjectPath = "./";

	for (i32 i = 1; i < argc; i++)
	{
		auto arg = std::string(argv[i]);
		// Quiet
		settings->Quiet = arg == "-q" || arg == "--quiet";
		// Target
		if (arg == "-t" || arg == "--target")
		{
			if (argc > i + 1)
				settings->CompileTarget = std::string(argv[i+1]);
		}

		// Last argument is a path if it doesn't start with a dash.
		if (i == argc - 1)
		{
			if (!arg.starts_with('-'))
				settings->ProjectPath = arg;
		}
	}
#pragma endregion

	// Print logo.
	if (!settings->Quiet)
		std::cout << SM_LOGO "\n";

	// Parse project.
	if (!settings->Quiet)
		std::cout << SM_PREFIX "Loading project\n";
	auto project = new Project(settings);

	// Compile.
	if (!settings->Quiet)
		std::cout << SM_PREFIX "Building "
		<< ((project->mType == smelt::ProjectType::Application) ? "application" : "library")
		<< " \"" << project->mName << "\" for " << settings->CompileTarget << "\n";
	project->Compile();
	
	// Cleanup.
	delete settings;
	delete project;

	// Exit successfully.
	return 0;
}
