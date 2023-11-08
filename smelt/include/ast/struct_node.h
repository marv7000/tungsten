#pragma once
#include "inode.h"

namespace smelt
{
	struct StructField
	{
		std::string mType;
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