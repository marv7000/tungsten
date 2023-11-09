#include "parser.h"
#include "code.h"
#include "ast/literal_node.h"
#include "ast/namespace_node.h"
#include "ast/call_node.h"
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
					Code::Namespaces.emplace_back(this);
					break;
				}
				case TokenType::KwStruct:
				{
					auto node = new StructNode(this);
					break;
				}
				case TokenType::KwMain:
				{
					Type returnType{};
					returnType.mName = "i32";
					Code::MainFunction = new FunctionNode(this, returnType, "main");
					break;
				}
				case TokenType::Identifier:
				{
					Type returnType = ParseType();
					GetNextToken();
					// Function or variable definition.
					if (mLastToken == TokenType::Identifier)
					{
						std::string name = mLexer->GetIdentifier();
						auto node = new FunctionNode(this, returnType, name);
					}
					// Function call.
					if (mLastToken == TokenType::BrOpRound)
					{
						std::string name = mLexer->GetIdentifier();
						auto node = new CallNode(this, name);
					}
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
		if (actual == type)
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
			case TokenType::LiNum:
			{
				std::cerr << "Expected a numeric literal!\n"; break;
			}
			case TokenType::LiAll:
			{
				std::cerr << "Expected a literal!\n"; break;
			}
		}

		exit(1);
	}

	std::string Parser::GetLine(u32 index) const
	{
		assert(index > 0); // 1-based indexing.
		std::vector<std::string> vec;
		std::string cur;
		auto pos = mLexer->GetStream().tellg(); // Save the position.
		mLexer->GetStream().seekg(0, std::ios_base::beg); // Go to beginning.

		// Read every line into vec.
		while (std::getline(mLexer->GetStream(), cur))
		{
			vec.emplace_back(cur);
		}

		mLexer->GetStream().seekg(pos, std::ios_base::beg); // Go back to original position.
		return vec[index - 1];
	}

	Type Parser::ParseType()
	{
		Type result{};

		Expect(TokenType::Identifier);
		result.mName = mLexer->GetIdentifier();

		// Built-in types don't have a namespace.
		if (result.mName != "i8" &&
			result.mName != "u8" &&
			result.mName != "i16" &&
			result.mName != "u16" &&
			result.mName != "i32" &&
			result.mName != "u32" &&
			result.mName != "i64" &&
			result.mName != "u64" &&
			result.mName != "float" &&
			result.mName != "double" &&
			result.mName != "bool" &&
			result.mName != "void"
			)
		{
			result.mNamespace = mLastNamespace;
		}

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
		if (mLastToken == TokenType::SyCaret)
		{
			result.mIsReference = true;
			GetNextToken();
		}

		return result;
	}

	TokenType Parser::GetNextToken()
	{
		return mLastToken = mLexer->GetToken();
	}
}
