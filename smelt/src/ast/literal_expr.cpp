#include "ast/literal_expr.h"
#include "code.h"
#include <llvm/IR/Constants.h>

namespace smelt
{
	LiteralExpr::LiteralExpr(Parser* parser)
	{
		mLiteralType = parser->mLastToken;
		mValue = parser->mLexer->GetLiteral();
	}

	llvm::Value* LiteralExpr::CodeGen()
	{
		switch (mLiteralType)
		{
			case TokenType::LiFloat:
			{
				return llvm::ConstantFP::get(llvm::Type::getFloatTy(Code::Context), llvm::StringRef(mValue));
			}
			case TokenType::LiDouble:
			{
				return llvm::ConstantFP::get(llvm::Type::getDoubleTy(Code::Context), llvm::StringRef(mValue));
			}
			default:
				break;
		}
		return nullptr;
	}
}
