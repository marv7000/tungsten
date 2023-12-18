#include "ast/string_literal_expr.h"
#include "code.h"
#include "project.h"
#include <llvm/IR/Constants.h>
#include <llvm/Support/FileSystem.h>

namespace smelt
{
	StringLiteralExpr::StringLiteralExpr(Parser* parser)
	{
		parser->Expect(TokenType::LiString);
		mValue = parser->mLexer->GetLiteral();
	}

	llvm::Value* StringLiteralExpr::CodeGen()
	{
		auto str = Code::Builder.CreateGlobalStringPtr(llvm::StringRef(mValue), "", 0, &Code::Module);

		std::error_code ec;
		llvm::raw_fd_ostream stream(Project::IntermediatePath, ec, llvm::sys::fs::OF_Append);
		str->print(stream);
		return str;
	}
}