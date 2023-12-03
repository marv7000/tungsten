#include <iostream>
#include "code.h"

namespace smelt
{
	void Code::Compile()
	{
		// Code generation.
		for (auto structure : Code::ParsedStructs)
		{
			auto* strc = structure->CodeGen();
			Code::Structs.push_back(strc);
			std::cout << "Struct:\t" << strc->getName().str() << "\n";
		}
		for (auto function : Code::ParsedFunctions)
		{
			auto* fun = function->CodeGen();
			Code::Functions.push_back(fun);
			std::cout << "Function:\t" << fun->getName().str() << "\n";
		}
		Code::MainFunction = Code::ParsedMainFunction->CodeGen();
	}

	llvm::Type *Code::TypeGen(const Type& s)
	{
		if (s.mName == "void")
			return llvm::Type::getVoidTy(Code::Context);
		else if (s.mName == "bool")
			return llvm::Type::getInt8Ty(Code::Context);
		else if (s.mName == "i8")
			return llvm::Type::getInt8Ty(Code::Context);
		else if (s.mName == "u8")
			return llvm::Type::getInt8Ty(Code::Context);
		else if (s.mName == "i16")
			return llvm::Type::getInt16Ty(Code::Context);
		else if (s.mName == "u16")
			return llvm::Type::getInt16Ty(Code::Context);
		else if (s.mName == "i32")
			return llvm::Type::getInt32Ty(Code::Context);
		else if (s.mName == "u32")
			return llvm::Type::getInt32Ty(Code::Context);
		else if (s.mName == "i64")
			return llvm::Type::getInt64Ty(Code::Context);
		else if (s.mName == "u64")
			return llvm::Type::getInt64Ty(Code::Context);
		else if (s.mName == "float")
			return llvm::Type::getFloatTy(Code::Context);
		else if (s.mName == "double")
			return llvm::Type::getDoubleTy(Code::Context);
		else
		{
			// Find struct if it already exists.
			return llvm::StructType::getTypeByName(Code::Context, s.mName);
		}
	}
}