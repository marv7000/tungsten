#pragma once
#include "parser.h"
#include "iexpr.h"

namespace smelt
{
	/// \brief 	An expression.
	class BinaryExpr : public IExpr
	{
		IExpr* mLhs;
		IExpr* mRhs;
	public:
		explicit BinaryExpr(Parser* parser);

		llvm::Value* CodeGen() override;
	};
}