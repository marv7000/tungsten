#pragma once
#include "inode.h"
#include <string>

namespace smelt
{
	class IntegerNode : public INode
	{
		std::string mValue;
	public:
		explicit IntegerNode(const std::string& value);
		llvm::Value* CodeGen(Parser* parser) override;
	};
}
