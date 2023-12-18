#include "ast/call_expr.h"
#include "code.h"
#include <iostream>
#include <utility>

namespace smelt
{
	CallExpr::CallExpr(Parser* parser, std::string& name, std::vector<IExpr*> args)
	{
		mName = name;
		mArgs = std::move(args);
		mPosition = ParserPosition(parser);
	}

	llvm::Value* CallExpr::CodeGen()
	{
		llvm::Function* callee = Code::Module.getFunction(mName);
		if (!callee)
		{
			mPosition.Error();
			std::cerr << "Function \"" << mName << "\" was not found!\n";
			exit(1);
		}

		// If argument mismatch error.
		if (callee->arg_size() != mArgs.size())
		{

		}

		std::vector<llvm::Value*> argsVec;
		for (auto mArg : mArgs) {
			argsVec.push_back(mArg->CodeGen());
			if (!argsVec.back())
				return nullptr;
		}

		return Code::Builder.CreateCall(callee, argsVec);
	}
}