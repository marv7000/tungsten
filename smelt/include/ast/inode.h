#pragma once
#include <llvm/IR/Value.h>
#include "parser.h"

namespace smelt
{

	/// \brief 	Represents an interface for a node in the abstract syntax tree.
	class INode
	{
	public:
		inline virtual llvm::Value* CodeGen(Parser* parser) { return nullptr; }
		virtual ~INode() = default;
	};
}
