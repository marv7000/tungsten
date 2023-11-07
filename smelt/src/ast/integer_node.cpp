#include "ast/integer_node.h"
#include <llvm/IR/Constants.h>

namespace smelt
{
	IntegerNode::IntegerNode(const std::string& value)
	{
		mValue = value;
	}

	llvm::Value* IntegerNode::CodeGen(Parser* parser)
	{
		llvm::IntegerType* type = llvm::IntegerType::get(*parser->mContext, 64);
		return llvm::ConstantInt::get(type, llvm::StringRef(mValue), 10);
	}
}
