#pragma once

#include "iexpr.h"

namespace smelt
{

	class StringLiteralExpr : public IExpr
	{
	public:
		std::string mValue;

		explicit StringLiteralExpr(Parser* parser);
		llvm::Value* CodeGen() override;
	};

} // smelt
