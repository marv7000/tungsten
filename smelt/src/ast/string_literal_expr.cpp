#include "ast/string_literal_expr.h"
#include "code.h"
#include <llvm/IR/Constants.h>

namespace smelt
{
	StringLiteralExpr::StringLiteralExpr(Parser* parser)
	{
		parser->Expect(TokenType::LiString);
		mValue = parser->mLexer->GetLiteral();
	}

	llvm::Value* StringLiteralExpr::CodeGen()
	{
		//auto arrayType = llvm::ArrayType::get(llvm::Type::getInt8Ty(Code::Context), mValue.size());
		std::vector<llvm::Constant*> data;
		for (auto& ch : mValue)
		{
			data.push_back(llvm::ConstantInt::get(llvm::Type::getInt8Ty(Code::Context), ch));
		}
		auto constStr = llvm::ConstantVector::get(data);
		return constStr;
	}
}