#pragma once
#include "iexpr.h"
#include "parser.h"

namespace smelt
{
	class VariableExpr : public IExpr
	{
		Type mType;
		std::string mName;
	public:
		explicit VariableExpr(Parser* parser);
		llvm::Value* CodeGen() override;
	};
}