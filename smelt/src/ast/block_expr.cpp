#include "ast/block_expr.h"
#include "code.h"

namespace smelt
{
	llvm::Value* BlockExpr::CodeGen()
	{
		llvm::Value* last;
		for (auto expr : mExpr)
		{
			last = expr->CodeGen();
		}
		return last;
	}
}