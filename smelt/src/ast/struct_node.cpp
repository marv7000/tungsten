#include "ast/struct_node.h"
#include <iostream>

namespace smelt
{
	StructNode::StructNode(Parser* parser)
	{
		// Eat struct keyword.
		parser->Expect(TokenType::KwStruct);

		parser->GetNextToken();
		parser->Expect(TokenType::Identifier);
		mName = parser->mLexer->GetIdentifier();

		parser->GetNextToken();
		parser->Expect(TokenType::BrOpCurly);

		// Parse fields.
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

		std::cout << "Parsed struct " << mName << " with fields\n";
		for (auto& field : mFields)
		{
			std::cout << "\tType: " << field.mType.mName << ", Name: " << field.mName << "\n";
		}
	}

	llvm::Value* StructNode::CodeGen()
	{

	}
}