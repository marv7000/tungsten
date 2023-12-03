#pragma once
#include <vector>
#include <string>
#include <map>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>

#include "ast/function_node.h"
#include "ast/struct_node.h"
#include "ast/type.h"

namespace smelt
{
	/// \brief 	Represents parsed code with all types, functions and namespaces.
	class Code
	{
	public:
		static inline llvm::LLVMContext Context = llvm::LLVMContext();
		static inline llvm::IRBuilder<> Builder = llvm::IRBuilder<>(Context);
		static inline llvm::Module Module = llvm::Module("tungstenJIT", Context);
		static inline std::vector<llvm::StructType*> Structs;
		static inline std::vector<llvm::Function*> Functions;
		static inline std::map<std::string, llvm::Value*> NamedValues;
		static inline llvm::Function* MainFunction;

		static inline std::vector<StructNode*> ParsedStructs;
		static inline std::vector<FunctionNode*> ParsedFunctions;
		static inline FunctionNode* ParsedMainFunction;

		static llvm::Type* TypeGen(const Type& s);

		/// \brief 	Compile all parsed code.
		static void Compile();
	};
}