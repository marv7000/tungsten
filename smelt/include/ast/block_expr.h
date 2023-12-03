#pragma once

#include "iexpr.h"
#include <vector>

namespace smelt
{
	class BlockExpr : public IExpr
	{
	public:
		std::vector<IExpr*> mExpr;
		llvm::Value* CodeGen() override;
	};
}