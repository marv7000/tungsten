#pragma once
#include "ast/type.h"
#include "ast/inode.h"
#include "parser.h"
#include <vector>
#include <llvm/IR/DerivedTypes.h>

namespace smelt
{
	class StructNode : public INode
	{
	public:
		std::string mName;
		std::vector<Type> mFields;
		std::vector<std::string> mFieldNames;
		std::vector<std::string> mGenericTypes;
		explicit StructNode(Parser* parser);

		llvm::StructType* CodeGen();
	};
}