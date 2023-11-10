#pragma once
#include "iexpr.h"
#include "token_type.h"
#include "parser.h"
#include <string>

namespace smelt
{
	class LiteralExpr : public IExpr
	{
		std::string mValue;
		TokenType mLiteralType;
	public:
		explicit LiteralExpr(Parser* parser);
		llvm::Value* CodeGen() override;
	};
}
