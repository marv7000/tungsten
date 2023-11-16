#include "parser.h"
#include "code.h"
#include "ast/literal_expr.h"
#include "ast/namespace_node.h"
#include "ast/call_expr.h"
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
		while (GetNextToken() != TokenType::Eof)
		{
			switch (mLastToken)
			{
				case TokenType::KwNamespace:
				{
					auto ns = NamespaceNode(this);
					break;
				}
				case TokenType::KwStruct:
				{
					Code::ParsedStructs.emplace_back(new StructNode(this));
					break;
				}
				case TokenType::KwMain:
				{
					Code::ParsedMainFunction = new FunctionNode(this, Type("i32"), "main");
					break;
				}
				case TokenType::Identifier:
				{
					Type returnType = ParseType();
					// Function or variable definition.
					Expect(TokenType::Identifier);
					std::string name = mLexer->GetIdentifier();
					Code::ParsedFunctions.emplace_back(new FunctionNode(this, returnType, name));
					break;
				}
				default:
					break;
			}
		}
	}

	void Parser::Expect(TokenType type) const
	{
		auto line = mLexer->GetTokenLineNumber();
		auto col = mLexer->GetTokenColNumber();
		auto actual = mLastToken;

		// Do bitwise comparison for literal bitflags.
		if ((i32)actual & (i32)type)
		{
			return;
		}

		std::cerr << "Syntax error: " << canonical(mLexer->GetPath()).string() << ":" << line << ":" << col << "\n";

		// Show which token is incorrect.
		std::cerr << line << "\t| " << GetLine(line) << "\n\t| ";

		for (i32 i = 1; i < col; i++)
		{
			std::cerr << " ";
		}

		std::cerr << "^ ";

		switch (type)
		{
			case TokenType::Eof:
			{
				std::cerr << "Expected and EOF token!\n"; break;
			}
			case TokenType::Identifier:
			{
				std::cerr << "Expected an identifier!\n"; break;
			}
			case TokenType::SySemicolon:
			{
				std::cerr << "Expected a ';'!\n"; break;
			}
			case TokenType::SyComma:
			{
				std::cerr << "Expected a ','!\n"; break;
			}
			case TokenType::SyDot:
			{
				std::cerr << "Expected a '.'!\n"; break;
			}
			case TokenType::SyQuestionMark:
			{
				std::cerr << "Expected a '?'!\n"; break;
			}
			case TokenType::SyExclamMark:
			{
				std::cerr << "Expected a '!'!\n"; break;
			}
			case TokenType::SyPlus:
			{
				std::cerr << "Expected a '+'!\n"; break;
			}
			case TokenType::SyMinus:
			{
				std::cerr << "Expected a '-'!\n"; break;
			}
			case TokenType::SyAsterisk:
			{
				std::cerr << "Expected a '*'!\n"; break;
			}
			case TokenType::SySlash:
			{
				std::cerr << "Expected a '/'!\n"; break;
			}
			case TokenType::SyBackSlash:
			{
				std::cerr << "Expected a '\\'!\n"; break;
			}
			case TokenType::SyPercent:
			{
				std::cerr << "Expected a '%'!\n"; break;
			}
			case TokenType::SyAmp:
			{
				std::cerr << "Expected a '&'!\n"; break;
			}
			case TokenType::SyEqual:
			{
				std::cerr << "Expected a '='!\n"; break;
			}
			case TokenType::SyCaret:
			{
				std::cerr << "Expected a '^'!\n"; break;
			}
			case TokenType::SyLess:
			{
				std::cerr << "Expected a '<'!\n"; break;
			}
			case TokenType::SyMore:
			{
				std::cerr << "Expected a '>'!\n"; break;
			}
			case TokenType::BrOpRound:
			{
				std::cerr << "Expected a '('!\n"; break;
			}
			case TokenType::BrClRound:
			{
				std::cerr << "Expected a ')'!\n"; break;
			}
			case TokenType::BrOpSquare:
			{
				std::cerr << "Expected a '['!\n"; break;
			}
			case TokenType::BrClSquare:
			{
				std::cerr << "Expected a ']'!\n"; break;
			}
			case TokenType::BrOpCurly:
			{
				std::cerr << "Expected a '{'!\n"; break;
			}
			case TokenType::BrClCurly:
			{
				std::cerr << "Expected a '}'!\n"; break;
			}
			case TokenType::KwInclude:
			{
				std::cerr << "Expected the \"include\" keyword!\n"; break;
			}
			case TokenType::KwNamespace:
			{
				std::cerr << "Expected the \"namespace\" keyword!\n"; break;
			}
			case TokenType::KwReturn:
			{
				std::cerr << "Expected the \"return\" keyword!\n"; break;
			}
			case TokenType::KwStruct:
			{
				std::cerr << "Expected the \"struct\" keyword!\n"; break;
			}
			case TokenType::KwHeap:
			{
				std::cerr << "Expected the \"heap\" keyword!\n"; break;
			}
			case TokenType::KwStack:
			{
				std::cerr << "Expected the \"stack\" keyword!\n"; break;
			}
			case TokenType::KwMain:
			{
				std::cerr << "Expected the \"main\" keyword!\n"; break;
			}
			case TokenType::LiString:
			{
				std::cerr << "Expected a string literal!\n"; break;
			}
			case TokenType::LiChar:
			{
				std::cerr << "Expected a character literal!\n"; break;
			}
			case TokenType::LiInt:
			{
				std::cerr << "Expected an integer literal!\n"; break;
			}
			case TokenType::LiFloat:
			case TokenType::LiDouble:
			{
				std::cerr << "Expected a floating point literal!\n"; break;
			}
			case TokenType::LiBool:
			{
				std::cerr << "Expected a boolean literal!\n"; break;
			}
			default: break;
		}

		if ((i32)type & (i32)TokenType::LiNum)
		{
			std::cerr << "Expected a numeric literal!\n";
		}
		else if ((i32)type & (i32)TokenType::LiAll)
		{
			std::cerr << "Expected a literal!\n";
		}

		exit(1);
	}

	std::string Parser::GetLine(u32 index) const
	{
		assert(index > 0); // 1-based indexing.
		std::vector<std::string> vec;
		std::string cur;
		mLexer->GetStream().clear(); // Clear all errors.
		auto pos = mLexer->GetStream().tellg(); // Save the position.
		mLexer->GetStream().seekg(0, std::ios_base::beg); // Go to beginning.

		// Read every line into vec.
		while (std::getline(mLexer->GetStream(), cur))
		{
			vec.emplace_back(cur);
		}

		mLexer->GetStream().seekg(pos, std::ios_base::beg); // Go back to original position.
		// Empty trailing lines aren't added.
		if (index <= vec.size())
			return vec[index - 1];
		return {};
	}

	Type Parser::ParseType()
	{
		Type result{};

		Expect(TokenType::Identifier);
		result.mName = mLexer->GetIdentifier();

		GetNextToken();

		// Generic types.
		if (mLastToken == TokenType::SyLess)
		{
			while (GetNextToken() != TokenType::Eof)
			{
				if (mLastToken == TokenType::Identifier)
				{
					result.mGenericTypes.emplace_back(ParseType());
				}
				// End.
				if (mLastToken == TokenType::SyMore)
					break;
			}
			GetNextToken();
		}
		// Array types.
		if (mLastToken == TokenType::BrOpSquare)
		{
			result.mIsArray = true;
			GetNextToken();
			if (mLastToken == TokenType::LiInt)
			{
				result.mArraySize = std::stoll(mLexer->GetLiteral());
				GetNextToken();
			}
			else
			{
				result.mArraySize = -1;
			}
			Expect(TokenType::BrClSquare);
			GetNextToken();
		}
		// References.
		if (mLastToken == TokenType::SyAmp)
		{
			result.mIsReference = true;
			GetNextToken();
		}

		return result;
	}

	TokenType Parser::GetNextToken()
	{
		return mLastToken = mLexer->GetToken(false);
	}

	TokenType Parser::PeekNextToken() const
	{
		return mLexer->GetToken(true);
	}
}
