#include "ast/variable_expr.h"
#include "code.h"

namespace smelt
{
	VariableExpr::VariableExpr(Parser* parser)
	{

	}

	llvm::Value* VariableExpr::CodeGen()
	{
		// TODO
		llvm::Value* val = Code::NamedValues[mName];
		//if (!val)

		return val;
	}
}