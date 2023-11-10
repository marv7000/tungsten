#pragma once
#include <llvm/IR/Value.h>
#include "parser.h"

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