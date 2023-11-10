#include "ast/struct_node.h"
#include <iostream>
#include "code.h"

namespace smelt
{
	StructNode::StructNode(Parser* parser)
	{
		// Eat struct keyword.
		parser->Expect(TokenType::KwStruct);

		parser->GetNextToken();
		parser->Expect(TokenType::Identifier);
		mName = parser->mLexer->GetIdentifier();

		// Generic Type arguments.
		if (parser->GetNextToken() == TokenType::SyLess)
		{
			while (parser->GetNextToken() != TokenType::Eof)
			{
				parser->Expect(TokenType::Identifier);
				auto id = parser->mLexer->GetIdentifier();
				mGenericTypes.emplace_back(id);
				if (parser->GetNextToken() != TokenType::SyComma)
					break;
			}
			parser->Expect(TokenType::SyMore);
		}

		// Parse fields.
		parser->GetNextToken();
		parser->Expect(TokenType::BrOpCurly);
		while (parser->GetNextToken() != TokenType::BrClCurly)
		{
			// Get the type of the field.
			Type t = parser->ParseType();

			// Get the name of the field.
			parser->Expect(TokenType::Identifier);
			std::string fieldName = parser->mLexer->GetIdentifier();

			// Has to be terminated by a semicolon.
			parser->GetNextToken();
			parser->Expect(TokenType::SySemicolon);

			mFields.emplace_back(t, fieldName);
		}
		mPosition = ParserPosition(parser);
	}

	llvm::Type* StructNode::CodeGen()
	{
		auto t = llvm::StructType::create(Code::Context, mName);
		Code::Structs.emplace_back(t);
		return t;
	}
}