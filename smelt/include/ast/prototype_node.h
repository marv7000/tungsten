#pragma once

#include "ast/type.h"
#include "parser.h"
#include "ast/inode.h"

namespace smelt
{
	class PrototypeNode : public INode
	{
	public:
		Type mReturnType;
		std::string mName;
		std::vector<Type> mArgs;
		std::vector<std::string> mArgNames;
		std::vector<Type> mGenericTypes;
		PrototypeNode(Parser* parser, const Type& returnType, const std::string& name);
		std::string Mangle();
	};
}