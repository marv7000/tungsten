#pragma once
#include "iexpr.h"
#include "parser.h"

namespace smelt
{
	/// \brief 	Represents a function call to a specific function.
	class CallExpr : public IExpr
	{
		std::string mName;
		std::vector<IExpr> mArgs;
	public:
		explicit CallExpr(Parser* parser, std::string& name);
	};
}