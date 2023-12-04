#include "ast/return_expr.h"
#include "code.h"

namespace smelt
{
	ReturnExpr::ReturnExpr(Parser* parser)
	{
		 parser->Expect(TokenType::KwReturn);
		 parser->GetNextToken();
		 if (parser->mLastToken == TokenType::SySemicolon)
			 return;
		 mExpr = IExpr::Parse(parser);
		 parser->GetNextToken();
		 parser->Expect(TokenType::SySemicolon);
	}

	llvm::Value* ReturnExpr::CodeGen()
	{
		if (!mExpr)
			return Code::Builder.CreateRetVoid();
		return Code::Builder.CreateRet(mExpr->CodeGen());
	}
}