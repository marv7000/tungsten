#include <iostream>
#include "ast/function_node.h"
#include "code.h"

#include <llvm/IR/Verifier.h>

namespace smelt
{
	FunctionNode::FunctionNode(Parser* parser, const Type& returnType, const std::string& name)
	{
		mPrototype = new PrototypeNode(parser, returnType, name);

		// Parse body expression.
		if (parser->GetNextToken() == TokenType::BrOpCurly)
		{
			// Start block.
			while (parser->mLastToken != TokenType::Eof)
			{
				parser->GetNextToken();
				IExpr* expr = IExpr::Parse(parser);

				parser->GetNextToken();
				if (parser->mLastToken == TokenType::BrClCurly)
					break;

				mBody = expr;
			}
			// End block.
			parser->Expect(TokenType::BrClCurly);
		}
		else
		{
			parser->Expect(TokenType::SySemicolon);
		}

		mPosition = ParserPosition(parser);
	}

	llvm::Function* FunctionNode::CodeGen()
	{
		if (!mPrototype)
			return nullptr;

		// TODO
		// Check for existing function with the same name.
		llvm::Function* fn = Code::Module.getFunction(mPrototype->mName);
		if (!fn)
			fn = Code::Module.getFunction(mPrototype->mName);
		if (!fn)
			return nullptr;

		// Create a new basic block to start insertion into.
		llvm::BasicBlock* block = llvm::BasicBlock::Create(Code::Context, "entry", fn);
		Code::Builder.SetInsertPoint(block);

		// Record the function arguments in the NamedValues map.
		Code::NamedValues.clear();
		for (auto &arg : fn->args())
		{
			Code::NamedValues[std::string(arg.getName())] = &arg;
		}

		if (mBody)
		{
			if (llvm::Value* retVal = mBody->CodeGen())
			{
				Code::Builder.CreateRet(retVal);
				llvm::verifyFunction(*fn);

				return fn;
			}
		}

		// Error reading body, remove function.
		fn->eraseFromParent();
		return nullptr;
	}
}