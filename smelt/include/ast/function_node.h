#pragma once
#include <string>
#include <vector>
#include "parser.h"
#include "inode.h"
#include "type.h"
#include "binary_expr.h"
#include "prototype_node.h"

namespace smelt
{
	class FunctionNode : public INode
	{
		PrototypeNode* mPrototype{};
		/// \brief 	Expression to execute or an extern function if null.
		IExpr* mBody{};
	public:
		explicit FunctionNode(Parser* parser, const Type& returnType, const std::string& name);

		llvm::Function* CodeGen();
	};
}