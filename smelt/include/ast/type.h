#pragma once
#include <llvm/IR/Type.h>
#include "namespace_node.h"

namespace smelt
{
	struct Type
	{
		NamespaceNode* mNamespace;
		llvm::Type* mType;
	};
}