#include "ast/call_expr.h"
#include <iostream>
#include <utility>

namespace smelt
{
	CallExpr::CallExpr(Parser* parser, std::string& name, std::vector<IExpr*> args)
	{
		mName = name;
		mArgs = std::move(args);
		std::cout << "Parsed function call " << name << " with " << mArgs.size() << " args.\n";
	}
}