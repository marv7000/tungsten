#include "ast/block_expr.h"

namespace smelt
{
	llvm::Value* BlockExpr::CodeGen()
	{
		IExpr* last = nullptr;
		for (auto expr : mExpr)
		{
			expr->CodeGen();
			last = expr;
		}
		if (!last)
		{
			return nullptr;
		}
		return last->CodeGen();
	}
}