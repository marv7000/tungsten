#pragma once
#include <vector>
#include <string>

#include "ast/namespace_node.h"
#include "ast/function_node.h"

namespace smelt
{
	/// \brief 	Represents parsed code with all types, functions and namespaces.
	class Code
	{
	public:
		static inline llvm::LLVMContext* Context = new llvm::LLVMContext();
		static inline llvm::IRBuilder<>* Builder = new llvm::IRBuilder<>(*Context);
		static inline llvm::Module* Module = new llvm::Module("tungstenJIT", *Context);

		static inline std::vector<NamespaceNode> Namespaces;
		static inline FunctionNode* MainFunction;
	};
}