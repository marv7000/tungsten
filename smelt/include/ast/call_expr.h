#pragma once
#include "iexpr.h"
#include "parser.h"

namespace smelt
{
	/// \brief 	Represents a function call to a specific function.
	class CallExpr : public IExpr
	{
	public:
		std::string mName;
		std::vector<IExpr*> mArgs;
		CallExpr(Parser* parser, std::string& name, std::vector<IExpr*> args);
		llvm::Value* CodeGen() override;
	};
}