#include <iostream>
#include <filesystem>

#include "shared.h"
#include "project.h"
#include "settings.h"
#include <llvm/TargetParser/Host.h>

using namespace smelt;

i32 main(const i32 argc, const i8** argv)
{
	// Parse arguments.
	auto settings = new Settings();
	for (i32 i = 1; i < argc; i++)
	{
		auto arg = std::string(argv[i]);
		settings->Quiet = arg == "-q" || arg == "--quiet";
	}

	// Print logo.
	std::cout << (settings->Quiet ? "" : SM_LOGO "\n");

	auto targetTriple = llvm::sys::getDefaultTargetTriple();
	std::cout << targetTriple << "\n";

	// Parse project.
	auto project = new Project(settings);


	// Cleanup.
	delete settings;
	delete project;

	// Exit.
	return 0;
}
