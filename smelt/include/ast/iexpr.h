#pragma once
#include "parser.h"
#include <llvm/IR/Value.h>

namespace smelt
{
	class IExpr
	{
	public:
		inline virtual llvm::Value* CodeGen() { return nullptr; }
		virtual ~IExpr() = default;

		static IExpr* Parse(Parser* parser);
	};

}