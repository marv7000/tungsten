#include "ast/struct_node.h"
#include <iostream>

namespace smelt
{
	StructNode::StructNode(Parser* parser)
	{
		// Eat struct keyword.
		parser->GetNextToken();
		parser->Expect(TokenType::KwStruct);

		parser->GetNextToken();
		parser->Expect(TokenType::Identifier);
		mName = parser->mLexer->GetIdentifier();

		parser->GetNextToken();
		parser->Expect(TokenType::BrOpCurly);

		while (parser->GetNextToken() != TokenType::BrClCurly)
		{
			parser->Expect(TokenType::Identifier);
			std::string fieldType = parser->mLexer->GetIdentifier();

			parser->GetNextToken();
			parser->Expect(TokenType::Identifier);
			std::string fieldName = parser->mLexer->GetIdentifier();

			parser->GetNextToken();
			parser->Expect(TokenType::SySemicolon);

			mFields.emplace_back(StructField{fieldType, fieldName});
		}

		std::cout << "Parsed struct " << mName << " with fields\n";
		for (auto& field : mFields)
		{
			std::cout << "\tType: " << field.mType << ", Name: " << field.mName << "\n";
		}
	}

	llvm::Value* StructNode::CodeGen()
	{

	}
}