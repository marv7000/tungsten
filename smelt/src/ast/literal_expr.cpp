#include "ast/literal_expr.h"
#include "code.h"
#include <llvm/IR/Constants.h>

namespace smelt
{
	LiteralExpr::LiteralExpr(Parser* parser)
	{
		parser->Expect(TokenType::LiAll);
		mLiteralType = parser->mLastToken;
		mValue = parser->mLexer->GetLiteral();
	}

	llvm::Value* LiteralExpr::CodeGen()
	{
		switch (mLiteralType)
		{
			case TokenType::LiInt:
			{
				// Remove separators.
				mValue.erase(std::remove(mValue.begin(), mValue.end(), '_'), mValue.end());

				// Hexadecimal
				if (mValue.starts_with("0x"))
				{
					return llvm::ConstantInt::get(llvm::Type::getInt64Ty(Code::Context), llvm::StringRef(mValue.substr(2)), 16);
				}
				// Binary
				if (mValue.starts_with("0b"))
				{
					return llvm::ConstantInt::get(llvm::Type::getInt64Ty(Code::Context), llvm::StringRef(mValue.substr(2)), 2);
				}
				return llvm::ConstantInt::get(llvm::Type::getInt64Ty(Code::Context), llvm::StringRef(mValue), 10);
			}
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
