#include "ast/call_expr.h"
#include <iostream>

namespace smelt
{
	CallExpr::CallExpr(Parser* parser, std::string& name)
	{
		mName = name;
		std::cout << "Parsed function call " << name << " with " << mArgs.size() << " args.\n";
	}
}