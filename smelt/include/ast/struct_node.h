#pragma once
#include "inode.h"
#include "type.h"

namespace smelt
{

	class StructNode : public INode
	{
		std::string mName;
		std::vector<NamedType> mFields;
		std::vector<std::string> mGenericTypes;
	public:
		explicit StructNode(Parser* parser);

		llvm::Type* CodeGen();
	};
}