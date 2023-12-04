#include <iostream>
#include "ast/iexpr.h"
#include "ast/call_expr.h"
#include "ast/literal_expr.h"
#include "ast/block_expr.h"
#include "parser_position.h"
#include "ast/int_literal_expr.h"
#include "ast/return_expr.h"
#include "ast/string_literal_expr.h"

namespace smelt
{
	IExpr* IExpr::Parse(Parser* parser)
	{
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
					block->mExpr.push_back(IExpr::Parse(parser));
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
						args.push_back(IExpr::Parse(parser));
						parser->GetNextToken();
					}
					parser->GetNextToken();
					return new CallExpr(parser, callee, args);
				}
				// TODO: Variable assignment.
				else if (parser->mLastToken == TokenType::SyEqual)
				{
					std::string id = parser->mLexer->GetIdentifier();

					parser->GetNextToken();
				}
				// TODO: Variable declaration.
				else if (parser->mLastToken == TokenType::Identifier)
				{
					parser->GetNextToken();
				}
				parser->Expect(TokenType::SySemicolon);
				return nullptr;
			}
			case TokenType::KwReturn:
			{
				return new ReturnExpr(parser);
			}
			case TokenType::LiInt:
			{
				return new IntLiteralExpr(parser);
			}
			case TokenType::LiString:
			{
				return new StringLiteralExpr(parser);
			}
			case TokenType::LiChar:
			case TokenType::LiBool:
			case TokenType::LiFloat:
			case TokenType::LiDouble:
			{
				return new LiteralExpr(parser);
			}
			default:
				auto pos = ParserPosition(parser);
				pos.Error();
				std::cerr << "Expected an expression.";
				exit(1);
		}
	}
}