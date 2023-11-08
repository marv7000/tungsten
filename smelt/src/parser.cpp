#include "parser.h"
#include "code.h"
#include "ast/literal_node.h"
#include "ast/namespace_node.h"
#include <iostream>

namespace smelt
{
	Parser::Parser(Lexer* lexer)
	{
		mLastToken = TokenType::Eof;
		mLexer = lexer;
	}

	void Parser::Parse()
	{
		// Main parsing loop.
		GetNextToken();
		switch (mLastToken)
		{
			case TokenType::KwNamespace:
			{
				Code::Namespaces.emplace_back(this);
			}
			case TokenType::KwStruct:
			{
				auto node = std::make_unique<StructNode>(this);
			}
			case TokenType::KwMain:
			{
				auto node = std::make_unique<FunctionNode>(this);
			}
			default:
				break;
		}
	}

	void Parser::Expect(TokenType type)
	{
		auto line = mLexer->GetLineNumber();
		auto col = mLexer->GetColNumber();
		auto actual = mLastToken;
		if (actual == type)
		{
			return;
		}

		std::cerr << "Error: Failure while parsing " << canonical(mLexer->GetPath()) << ":\n\t";
		switch (type)
		{
			case TokenType::Eof:
			{
				std::cerr << "Expected and EOF token at " << line << "," << col << "!\n"; break;
			}
			case TokenType::Identifier:
			{
				std::cerr << "Expected an identifier at " << line << "," << col << "!\n"; break;
			}
			case TokenType::SySemicolon:
			{
				std::cerr << "Expected a '?' at " << line << "," << col << "!\n"; break;
			}
			case TokenType::SyComma:
			{
				std::cerr << "Expected a ',' at " << line << "," << col << "!\n"; break;
			}
			case TokenType::SyDot:
			{
				std::cerr << "Expected a '.' at " << line << "," << col << "!\n"; break;
			}
			case TokenType::SyQuestionMark:
			{
				std::cerr << "Expected a '?' at " << line << "," << col << "!\n"; break;
			}
			case TokenType::SyExclamMark:
			{
				std::cerr << "Expected a '!' at " << line << "," << col << "!\n"; break;
			}
			case TokenType::SyPlus:
			{
				std::cerr << "Expected a '+' at " << line << "," << col << "!\n"; break;
			}
			case TokenType::SyMinus:
			{
				std::cerr << "Expected a '-' at " << line << "," << col << "!\n"; break;
			}
			case TokenType::SyAsterisk:
			{
				std::cerr << "Expected a '*' at " << line << "," << col << "!\n"; break;
			}
			case TokenType::SySlash:
			{
				std::cerr << "Expected a '/' at " << line << "," << col << "!\n"; break;
			}
			case TokenType::SyBackSlash:
			{
				std::cerr << "Expected a '\\' at " << line << "," << col << "!\n"; break;
			}
			case TokenType::SyPercent:
			{
				std::cerr << "Expected a '%' at " << line << "," << col << "!\n"; break;
			}
			case TokenType::SyEqual:
			{
				std::cerr << "Expected a '=' at " << line << "," << col << "!\n"; break;
			}
			case TokenType::SyCaret:
			{
				std::cerr << "Expected a '^' at " << line << "," << col << "!\n"; break;
			}
			case TokenType::SyLess:
			{
				std::cerr << "Expected a '<' at " << line << "," << col << "!\n"; break;
			}
			case TokenType::SyMore:
			{
				std::cerr << "Expected a '>' at " << line << "," << col << "!\n"; break;
			}
			case TokenType::BrOpRound:
			{
				std::cerr << "Expected a '(' at " << line << "," << col << "!\n"; break;
			}
			case TokenType::BrClRound:
			{
				std::cerr << "Expected a ')' at " << line << "," << col << "!\n"; break;
			}
			case TokenType::BrOpSquare:
			{
				std::cerr << "Expected a '[' at " << line << "," << col << "!\n"; break;
			}
			case TokenType::BrClSquare:
			{
				std::cerr << "Expected a ']' at " << line << "," << col << "!\n"; break;
			}
			case TokenType::BrOpCurly:
			{
				std::cerr << "Expected a '{' at " << line << "," << col << "!\n"; break;
			}
			case TokenType::BrClCurly:
			{
				std::cerr << "Expected a '}' at " << line << "," << col << "!\n"; break;
			}
			case TokenType::KwInclude:
			{
				std::cerr << "Expected the \"include\" keyword at " << line << "," << col << "!\n"; break;
			}
			case TokenType::KwNamespace:
			{
				std::cerr << "Expected the \"namespace\" keyword at " << line << "," << col << "!\n"; break;
			}
			case TokenType::KwReturn:
			{
				std::cerr << "Expected the \"return\" keyword at " << line << "," << col << "!\n"; break;
			}
			case TokenType::KwStruct:
			{
				std::cerr << "Expected the \"struct\" keyword at " << line << "," << col << "!\n"; break;
			}
			case TokenType::KwHeap:
			{
				std::cerr << "Expected the \"heap\" keyword at " << line << "," << col << "!\n"; break;
			}
			case TokenType::KwStack:
			{
				std::cerr << "Expected the \"stack\" keyword at " << line << "," << col << "!\n"; break;
			}
			case TokenType::KwMain:
			{
				std::cerr << "Expected the \"main\" keyword at " << line << "," << col << "!\n"; break;
			}
			case TokenType::LiString:
			{
				std::cerr << "Expected a string literal at " << line << "," << col << "!\n"; break;
			}
			case TokenType::LiChar:
			{
				std::cerr << "Expected a character literal at " << line << "," << col << "!\n"; break;
			}
			case TokenType::LiInt:
			{
				std::cerr << "Expected an integer literal at " << line << "," << col << "!\n"; break;
			}
			case TokenType::LiFloat:
			case TokenType::LiDouble:
			{
				std::cerr << "Expected a floating point literal at " << line << "," << col << "!\n"; break;
			}
			case TokenType::LiBool:
			{
				std::cerr << "Expected a boolean literal at " << line << "," << col << "!\n"; break;
			}
			case TokenType::LiNum:
			{
				std::cerr << "Expected a numeric literal at " << line << "," << col << "!\n"; break;
			}
			case TokenType::LiAll:
			{
				std::cerr << "Expected a literal at " << line << "," << col << "!\n"; break;
			}
		}

		exit(1);
	}
}
