#pragma once
#include "inode.h"
#include "type.h"

namespace smelt
{
	struct StructField
	{
		Type mType;
		std::string mName;
	};

	class StructNode : public INode
	{
		std::string mName;
		std::vector<StructField> mFields;
	public:
		explicit StructNode(Parser* parser);

		llvm::Value* CodeGen() override;
	};
}