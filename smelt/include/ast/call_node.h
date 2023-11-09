#pragma once
#include "inode.h"

namespace smelt
{
	class CallNode : public INode
	{
		std::string mName;
	public:
		explicit CallNode(Parser* parser, std::string& name);
	};
}