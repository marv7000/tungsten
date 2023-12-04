#include <llvm/IR/Constants.h>
#include "ast/int_literal_expr.h"
#include "code.h"

namespace smelt
{
	IntLiteralExpr::IntLiteralExpr(Parser* parser)
	{
		parser->Expect(TokenType::LiInt);
		mValue = parser->mLexer->GetLiteral();
	}

	llvm::Value* IntLiteralExpr::CodeGen()
	{
		// Remove separators.
		mValue.erase(std::remove(mValue.begin(), mValue.end(), '_'), mValue.end());

		// Hexadecimal
		if (mValue.starts_with("0x"))
		{
			return llvm::ConstantInt::get(llvm::Type::getInt32Ty(Code::Context), llvm::StringRef(mValue.substr(2)), 16);
		}
		// Binary
		if (mValue.starts_with("0b"))
		{
			return llvm::ConstantInt::get(llvm::Type::getInt32Ty(Code::Context), llvm::StringRef(mValue.substr(2)), 2);
		}
		return llvm::ConstantInt::get(llvm::Type::getInt32Ty(Code::Context), llvm::StringRef(mValue), 10);
	}

}