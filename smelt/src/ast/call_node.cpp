#include "ast/call_node.h"

namespace smelt
{
	CallNode::CallNode(Parser* parser, std::string& name)
	{
		mName = name;
	}
}