#include "ast/prototype_node.h"

namespace smelt
{
	PrototypeNode::PrototypeNode(Parser* parser, const Type& returnType, const std::string& name)
	{
		mReturnType = returnType;
		mName = name;

		// Special case: main method.
		if (parser->mLastToken == TokenType::KwMain)
		{
			Type t("str", false, true);
			mArgs.emplace_back(t, "args");
		}
		// Parse function declaration.
		else
		{
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

			// Arguments.
			parser->Expect(TokenType::BrOpRound);
			while (parser->GetNextToken() != TokenType::Eof)
			{
				Type t = parser->ParseType();

				parser->Expect(TokenType::Identifier);

				mArgs.emplace_back(t, parser->mLexer->GetIdentifier());
				if (parser->GetNextToken() == TokenType::BrClRound)
					break;
				parser->Expect(TokenType::SyComma);
			}
		}
		mPosition = ParserPosition(parser);
	}
}