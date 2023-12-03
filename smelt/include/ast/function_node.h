#pragma once
#include <string>
#include <vector>
#include "parser.h"
#include "ast/inode.h"
#include "ast/iexpr.h"
#include "ast/prototype_node.h"
#include "ast/type.h"

namespace smelt
{
	class FunctionNode : public INode
	{
	public:
		PrototypeNode* mPrototype{};
		/// \brief 	Expression to execute or an extern function if null.
		IExpr* mBody{};
		FunctionNode(Parser* parser, const Type& returnType, const std::string& name);

		llvm::Function* CodeGen();
	};
}