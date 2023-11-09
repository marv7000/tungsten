#pragma once
#include <string>
#include <vector>
#include "parser.h"
#include "inode.h"
#include "type.h"

namespace smelt
{
	class FunctionNode : public INode
	{
		Type mReturnType;
		std::string mName;
		std::vector<Type> mArgs;
	public:
		explicit FunctionNode(Parser* parser, const Type& returnType, const std::string& name);

		llvm::Value* CodeGen() override;
	};
}