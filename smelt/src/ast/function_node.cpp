#include <iostream>
#include "ast/function_node.h"
#include "code.h"

namespace smelt
{
	FunctionNode::FunctionNode(Parser* parser, const Type& returnType, const std::string& name)
	{
		mReturnType = returnType;
		mName = name;
		// Special case: main method.
		if (parser->mLastToken == TokenType::KwMain)
		{
			mArgs.emplace_back("", "str", true, false, -1);
		}
		else
		{
			parser->GetNextToken();
			parser->Expect(TokenType::BrOpRound);
			parser->GetNextToken();
			while (parser->mLastToken != TokenType::Eof)
			{
				Type t = parser->ParseType();

				parser->Expect(TokenType::Identifier);

				mArgs.emplace_back(t);
				if (parser->GetNextToken() == TokenType::BrClRound)
					break;
			}
		}

		std::cout << "Parsed function \"" << mName << "\" with return type \"" << mReturnType.mName << "\" and args:\n";
		for (auto& arg : mArgs)
		{
			std::cout << "\tType: " << arg.mName << "\n";
		}
	}

	llvm::Value* FunctionNode::CodeGen()
	{
		return INode::CodeGen();
	}
}