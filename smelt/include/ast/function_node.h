#pragma once
#include <string>
#include <vector>
#include "parser.h"
#include "inode.h"

namespace smelt
{
	class FunctionNode : public INode
	{
		std::string mName;
		std::string mReturnType;
		std::vector<std::string> mArgs;
	public:
		explicit FunctionNode(Parser* parser);

		llvm::Value* CodeGen() override;
	};
}