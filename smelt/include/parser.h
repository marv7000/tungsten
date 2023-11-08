#pragma once
#include "shared.h"
#include "lexer.h"

#include <llvm/IR/IRBuilder.h>

namespace smelt
{
    class Parser
    {
    public:
		TokenType mLastToken;
		Lexer* mLexer;

		explicit Parser(Lexer* lexer);

		/// \brief 	Parses the stream opened by the lexer.
		/// \return The root node containing the entire tree.
		void Parse();

		inline TokenType GetNextToken()
		{
			return mLastToken = mLexer->GetToken();
		}

		/// \brief 		Expect the next token in the stream to be a certain type. If it isn't, throw a fitting message.
		/// \param type The type to check for.
	    void Expect(TokenType type);
    };
}
