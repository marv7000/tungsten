#pragma once

#include "iexpr.h"

namespace smelt
{

	class IntLiteralExpr : public IExpr
	{
	public:
		std::string mValue;
		explicit IntLiteralExpr(Parser* parser);
		llvm::Value* CodeGen() override;
	};

} // smelt
