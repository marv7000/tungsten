#pragma once

#include "iexpr.h"

namespace smelt
{
	class ReturnExpr : public IExpr
	{
	public:
		IExpr* mExpr = nullptr;
		explicit ReturnExpr(Parser* parser);

		llvm::Value* CodeGen() override;
	};
}
