#include <iostream>
#include "ast/variable_expr.h"
#include "code.h"

namespace smelt
{
	VariableExpr::VariableExpr(Parser* parser, const Type& type, const std::string& name, IExpr* value)
	{
		mPosition = ParserPosition(parser);
		mValue = value;
		mName = name;
		Code::VariableNames[name] = this;
	}

	llvm::Value* VariableExpr::CodeGen()
	{
		// TODO
		if (!mValue)
		{
			if (Code::NamedValues[mName])
			{
				return Code::NamedValues[mName];
			}
			mPosition.Error();
			std::cerr << "Unknown variable \"" << mName << "\"\n";
			exit(1);
		}
		return mValue->CodeGen();
	}
}