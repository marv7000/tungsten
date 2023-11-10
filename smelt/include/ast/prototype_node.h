#pragma once
#include "parser.h"
#include "ast/inode.h"

namespace smelt
{
	class PrototypeNode : public INode
	{
	public:
		Type mReturnType;
		std::string mName;
		std::vector<NamedType> mArgs;
		std::vector<std::string> mGenericTypes;
		explicit PrototypeNode(Parser* parser, const Type& returnType, const std::string& name);
	};
}