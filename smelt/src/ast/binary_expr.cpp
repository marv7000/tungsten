#include "ast/binary_expr.h"

namespace smelt
{
	BinaryExpr::BinaryExpr(Parser* parser)
	{
		mLhs = nullptr;
	}

	llvm::Value* BinaryExpr::CodeGen()
	{
		// TODO
		return nullptr;
	}
}