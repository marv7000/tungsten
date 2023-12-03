#include <iostream>
#include "ast/iexpr.h"
#include "ast/call_expr.h"
#include "ast/literal_expr.h"
#include "ast/block_expr.h"

namespace smelt
{
	IExpr* IExpr::Parse(Parser* parser)
	{
		IExpr* result = nullptr;

		// Start Scoped expression.
		switch (parser->mLastToken)
		{
			case TokenType::BrOpCurly:
			{
				auto block = new BlockExpr();
				while (parser->mLastToken != TokenType::Eof)
				{
					parser->GetNextToken();
					if (parser->mLastToken == TokenType::BrClCurly)
						break;
					block->mExpr.emplace_back(IExpr::Parse(parser));
				}
				return block;
			}
			case TokenType::Identifier:
			{
				parser->GetNextToken();
				// Function call.
				if (parser->mLastToken == TokenType::BrOpRound)
				{
					std::string callee = parser->mLexer->GetIdentifier();
					std::vector<IExpr*> args;

					// Call arguments.
					parser->GetNextToken();
					while (parser->mLastToken != TokenType::Eof)
					{
						// No args.
						if (parser->mLastToken == TokenType::BrClRound)
							break;
						// Literal or identifier.
						if (parser->mLastToken == TokenType::Identifier)
							args.emplace_back(IExpr::Parse(parser));
						if ((i32)parser->mLastToken & (i32)TokenType::LiAll)
							args.emplace_back(new LiteralExpr(parser));
						parser->GetNextToken();
					}
					parser->GetNextToken();
					result = new CallExpr(parser, callee, args);
				}
				// Variable assignment.
				else if (parser->mLastToken == TokenType::SyEqual)
				{
					std::string id = parser->mLexer->GetIdentifier();

					parser->GetNextToken();
				}
				// Variable declaration.
				else if (parser->mLastToken == TokenType::Identifier)
				{
					parser->GetNextToken();
				}
				parser->Expect(TokenType::SySemicolon);
			}
			default:
				return result;
		}
	}
}