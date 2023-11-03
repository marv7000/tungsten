#include <iostream>
#include <filesystem>
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

#include "shared.h"
#include "project.h"
#include "settings.h"

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
	
	// Parse project.
	auto project = new Project(settings);

	{
		auto targetTriple = llvm::sys::getDefaultTargetTriple();
		std::cout << targetTriple << "\n";

	}

	// Cleanup.
	delete settings;
	delete project;

	// Exit.
	return 0;
}
