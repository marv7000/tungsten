#pragma once
#include "inode.h"

namespace smelt
{
	/// \brief 	Represents a namespace by storing its name, the respective function and type identifiers.
	class NamespaceNode : public INode
	{
		std::string mValue;
	public:
		explicit NamespaceNode(const std::string& value);
		llvm::Value* CodeGen(Parser* parser) override;
	};
}
