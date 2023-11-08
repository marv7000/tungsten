#include <iostream>
#include "ast/function_node.h"
#include "code.h"

namespace smelt
{
	FunctionNode::FunctionNode(Parser* parser)
	{
		parser->GetNextToken();
		// Special case: main method.
		if (parser->mLastToken == TokenType::KwMain)
		{
			mReturnType = "i32";
			mArgs.emplace_back("str[]");
			mName = "main";
		}
		else
		{
			while (parser->GetNextToken() != TokenType::BrClRound)
			{
				parser->Expect(TokenType::SyComma);
			}

			parser->Expect(TokenType::Identifier);
		}

		std::cout << "Parsed function \"" << mName << "\" with return type \"" << mReturnType << "\" and args:\n";
		for (auto& arg : mArgs)
		{
			std::cout << "\tType: " << arg << "\n";
		}
	}

	llvm::Value *FunctionNode::CodeGen()
	{
		return INode::CodeGen();
	}
}