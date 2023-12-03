#pragma once

#include "shared.h"
#include "lexer.h"
#include "ast/type.h"

namespace smelt
{
    class Parser
    {
    public:
	    std::string mLastNamespace;
	    std::string mLastStruct;
	    std::string mLastFn;
		TokenType mLastToken;
		Lexer* mLexer;

		explicit Parser(Lexer* lexer);

		/// \brief 	Parses the stream opened by the lexer.
		/// \return The root node containing the entire tree.
		void Parse();

	    /// \brief 		Expect the next token in the stream to be a certain type. If it isn't, throw a fitting message.
	    /// \param type The type to check for.
	    void Expect(TokenType type);

		TokenType GetNextToken();
		[[nodiscard]] TokenType PeekNextToken() const;

		/// \brief 			Gets a specific line in the file.
		/// \param index 	The line number, 1-based index.
		/// \return			The line as a string.
		[[nodiscard]] std::string GetLine(u32 index) const;

		Type ParseType();
    };
}
