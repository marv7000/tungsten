#include "ast/namespace_node.h"

namespace smelt
{

	NamespaceNode::NamespaceNode(const std::string& value)
	{
		mValue = value;
	}

	llvm::Value* NamespaceNode::CodeGen(Parser* parser)
	{
		return INode::CodeGen(parser);
	}
}
