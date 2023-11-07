#include "parser.h"
#include "ast/integer_node.h"

namespace smelt
{
	Parser::Parser(Lexer* lexer)
	{
		mLastToken = TokenType::Eof;
		mLexer = lexer;

		mContext = std::make_unique<llvm::LLVMContext>();
		mModule = std::make_unique<llvm::Module>("jit", *mContext);
		mBuilder = std::make_unique<llvm::IRBuilder<>>(*mContext);
	}

	void Parser::Parse()
	{
		// Main parsing loop.
		switch (mLastToken)
		{
			case TokenType::KwNamespace:
			{

			}
			case TokenType::LiInt:
			{
				auto node = std::make_unique<IntegerNode>(mLexer->GetLiteral());
			}
			default:
				break;
		}
	}
}
