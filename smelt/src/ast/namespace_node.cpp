#include "ast/namespace_node.h"

namespace smelt
{
	NamespaceNode::NamespaceNode(Parser* parser)
	{
		// Eat namespace token.
		parser->GetNextToken();
		parser->Expect(TokenType::Identifier);

		mName = parser->mLexer->GetIdentifier();

		// Eat semicolon.
		parser->GetNextToken();
		parser->Expect(TokenType::SySemicolon);

		parser->mLastNamespace = mName;

		mPosition = ParserPosition(parser);
	}

	llvm::Value* NamespaceNode::CodeGen()
	{
		return nullptr;
	}
}
