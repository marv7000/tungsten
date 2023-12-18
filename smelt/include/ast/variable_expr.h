#pragma once
#include "iexpr.h"
#include "parser.h"
#include "parser_position.h"

namespace smelt
{
	class VariableExpr : public IExpr
	{
		Type mType;
		std::string mName;
		ParserPosition mPosition;
		IExpr* mValue;
	public:
		VariableExpr(Parser* parser, const Type& type, const std::string& name, IExpr* value);
		llvm::Value* CodeGen() override;
	};
}