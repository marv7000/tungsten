#pragma once
#include "iexpr.h"
#include "token_type.h"
#include "parser.h"
#include <string>

namespace smelt
{
	class LiteralExpr : public IExpr
	{
	public:
		std::string mValue;
		TokenType mLiteralType;
		explicit LiteralExpr(Parser* parser);
		llvm::Value* CodeGen() override;
	};
}
