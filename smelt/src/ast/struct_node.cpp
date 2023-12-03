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
			parser->GetNextToken();
		}

		// Parse fields.
		parser->Expect(TokenType::BrOpCurly);
		while (parser->GetNextToken() != TokenType::Eof)
		{
			if (parser->mLastToken == TokenType::BrClCurly)
				break;

			parser->Expect(TokenType::Identifier);
			// Get the type of the field.
			Type t = parser->ParseType();

			// Get the name of the field.
			parser->Expect(TokenType::Identifier);
			std::string fieldName = parser->mLexer->GetIdentifier();

			// Has to be terminated by a semicolon.
			parser->GetNextToken();
			parser->Expect(TokenType::SySemicolon);

			mFields.emplace_back(t);
			mFieldNames.emplace_back(fieldName);
		}
		parser->Expect(TokenType::BrClCurly);
		mPosition = ParserPosition(parser);
	}

	llvm::StructType* StructNode::CodeGen()
	{
		auto types = std::vector<llvm::Type*>();
		for (const auto & field : mFields)
		{
			types.push_back(Code::TypeGen(field));
		}
		auto t = llvm::StructType::create(Code::Context, types, mName);
		return t;
	}
}