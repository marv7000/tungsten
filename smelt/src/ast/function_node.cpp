#include <iostream>
#include "ast/function_node.h"
#include "code.h"

#include <llvm/IR/Verifier.h>

namespace smelt
{
	FunctionNode::FunctionNode(Parser* parser, const Type& returnType, const std::string& name)
	{
		mPrototype = new PrototypeNode(parser, returnType, name);
		parser->GetNextToken();
		if (parser->mLastToken != TokenType::SySemicolon)
		{
			IExpr* expr = IExpr::Parse(parser);
			if (expr)
			{
				mBody = expr;
			}
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
		if (fn)
		{
			mPosition.Error();
			std::cerr << "Function " << mPrototype->mName << " has already been defined.";
			exit(1);
		}

		// Create a function type from args and return type.
		std::vector<llvm::Type*> argTypes;
		for (auto& arg : mPrototype->mArgs)
		{
			argTypes.emplace_back(Code::TypeGen(arg));
		}
		auto retType = Code::TypeGen(mPrototype->mReturnType);
		llvm::FunctionType* fnType = llvm::FunctionType::get(retType, argTypes, false);

		if (mBody)
		{
			fn = llvm::Function::Create(fnType, llvm::Function::CommonLinkage, mPrototype->mName);
			// Record the function arguments in the NamedValues map.
			Code::NamedValues.clear();
			for (auto &arg : fn->args())
			{
				Code::NamedValues[std::string(arg.getName())] = &arg;
			}

			// Create a new basic block to start insertion into.
			llvm::BasicBlock* block = llvm::BasicBlock::Create(Code::Context, "entry", fn);
			Code::Builder.SetInsertPoint(block);
			llvm::Value* retVal = mBody->CodeGen();
			if (retVal)
			{
				Code::Builder.CreateRet(retVal);
				fn->print(llvm::outs());
				llvm::verifyFunction(*fn);

				Code::Functions.emplace_back(fn);
				return fn;
			}
			return nullptr;
		}
		// External linkage.
		else
		{
			fn = llvm::Function::Create(fnType, llvm::Function::ExternalLinkage, mPrototype->mName, Code::Module);
			Code::Functions.emplace_back(fn);
			return fn;
		}

	}
}