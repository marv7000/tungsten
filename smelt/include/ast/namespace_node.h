#pragma once
#include <vector>
#include "inode.h"
#include "struct_node.h"
#include "function_node.h"

namespace smelt
{
	/// \brief 	Represents a namespace by storing its name, the respective function and type identifiers.
	class NamespaceNode : public INode
	{
		std::string mName;
	public:
		explicit NamespaceNode(Parser* parser);
		llvm::Value* CodeGen();
	};
}
