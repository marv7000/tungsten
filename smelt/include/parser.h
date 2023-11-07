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
		std::unique_ptr<llvm::LLVMContext> mContext;
		std::unique_ptr<llvm::IRBuilder<>> mBuilder;
		std::unique_ptr<llvm::Module> mModule;

		explicit Parser(Lexer* lexer);

		/// \brief 	Parses the stream opened by the lexer.
		/// \return The root node containing the entire tree.
		void Parse();

		inline TokenType GetNextToken()
		{
			return mLastToken = mLexer->GetToken();
		}
    };
}
