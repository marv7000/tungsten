#include <iostream>
#include "ast/function_node.h"
#include "code.h"
#include "project.h"

#include <llvm/IR/Verifier.h>
#include <llvm/Support/FileSystem.h>

namespace smelt
{
	FunctionNode::FunctionNode(Parser* parser, const Type& returnType, const std::string& name)
	{
		mPrototype = new PrototypeNode(parser, returnType, name);
		parser->GetNextToken();
		if (parser->mLastToken == TokenType::SySemicolon)
		{
			return;
		}
		mPosition = ParserPosition(parser);
		mBody = IExpr::Parse(parser);
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
			std::cerr << "Function \"" << mPrototype->mName << "\" has already been defined.";
			exit(1);
		}

		// Create a function type from args and return type.
		std::vector<llvm::Type*> argTypes;
		for (auto& arg : mPrototype->mArgs)
		{
			argTypes.push_back(Code::TypeGen(arg));
		}
		auto retType = Code::TypeGen(mPrototype->mReturnType);
		llvm::FunctionType* fnType = llvm::FunctionType::get(retType, argTypes, false);

		if (mBody)
		{
			fn = llvm::Function::Create(fnType, llvm::Function::LinkageTypes::ExternalLinkage, mPrototype->Mangle(), Code::Module);
			// Record the function arguments in the NamedValues map.
			Code::NamedValues.clear();
			for (auto &arg : fn->args())
			{
				Code::NamedValues[std::string(arg.getName())] = &arg;
			}
			for (auto& arg : Code::VariableNames)
			{
				Code::NamedValues[arg.first] = arg.second->CodeGen();
			}

			// Create a new basic block to start insertion into.
			llvm::BasicBlock* block = llvm::BasicBlock::Create(Code::Context, "entry", fn);
			Code::Builder.SetInsertPoint(block);
			llvm::Value* retVal = mBody->CodeGen();
			if (retVal)
			{
				std::error_code ec;
				llvm::raw_fd_ostream stream(Project::IntermediatePath, ec, llvm::sys::fs::OF_Append);
				fn->print(stream);

				// TODO: Fix error
				assert(!llvm::verifyModule(Code::Module, &llvm::errs()));
				assert(!llvm::verifyFunction(*fn, &llvm::errs()));

				Code::Functions.push_back(fn);
				return fn;
			}
			return nullptr;
		}
		// External linkage.
		else
		{
			fn = llvm::Function::Create(fnType, llvm::Function::ExternalLinkage, mPrototype->Mangle(), Code::Module);
			std::error_code ec;
			llvm::raw_fd_ostream stream(Project::IntermediatePath, ec, llvm::sys::fs::OF_Append);
			fn->print(stream);
			assert(!llvm::verifyModule(Code::Module, &llvm::errs()));
			assert(!llvm::verifyFunction(*fn, &llvm::errs()));
			Code::Functions.push_back(fn);
			return fn;
		}

	}
}