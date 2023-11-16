#include <iostream>
#include "ast/iexpr.h"
#include "ast/call_expr.h"
#include "ast/literal_expr.h"

namespace smelt
{
	IExpr* IExpr::Parse(Parser* parser)
	{
		IExpr* result = nullptr;
		while (parser->mLastToken != TokenType::Eof)
		{
			// Either a variable or function call.
			if (parser->mLastToken == TokenType::Identifier)
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
				parser->GetNextToken();
			}
		}
		return result;
	}
}