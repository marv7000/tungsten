#pragma once
#include "inode.h"
#include <string>

namespace smelt
{
	class LiteralNode : public INode
	{
		std::string mValue;
		TokenType mLiteralType;
	public:
		explicit LiteralNode(Parser* parser);
		llvm::Value* CodeGen() override;
	};
}
