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
		}
		for (auto function : Code::ParsedFunctions)
		{
			auto* fun = function->CodeGen();
			Code::Functions.push_back(fun);
		}
	}

	llvm::Type* Code::TypeGen(const Type& s)
	{
		llvm::Type* result;
		if (s.mName == "void")
			result = llvm::Type::getVoidTy(Code::Context);
		else if (s.mName == "bool")
			result = llvm::Type::getInt8Ty(Code::Context);
		else if (s.mName == "i8")
			result = llvm::Type::getInt8Ty(Code::Context);
		else if (s.mName == "u8")
			result = llvm::Type::getInt8Ty(Code::Context);
		else if (s.mName == "i16")
			result = llvm::Type::getInt16Ty(Code::Context);
		else if (s.mName == "u16")
			result = llvm::Type::getInt16Ty(Code::Context);
		else if (s.mName == "i32")
			result = llvm::Type::getInt32Ty(Code::Context);
		else if (s.mName == "u32")
			result = llvm::Type::getInt32Ty(Code::Context);
		else if (s.mName == "i64")
			result = llvm::Type::getInt64Ty(Code::Context);
		else if (s.mName == "u64")
			result = llvm::Type::getInt64Ty(Code::Context);
		else if (s.mName == "float")
			result = llvm::Type::getFloatTy(Code::Context);
		else if (s.mName == "double")
			result = llvm::Type::getDoubleTy(Code::Context);
		else
		{
			// Find struct if it already exists.
			auto val = llvm::StructType::getTypeByName(Code::Context, s.mName);
			if (val)
				result = val;
			else
			{
				std::cerr << "Unknown type or structure \"" << s.mName << "\"!\n";
				exit(1);
			}
		}

		if (s.mIsArray)
		{
			if (s.mArraySize == -1)
				result = llvm::PointerType::get(result, 0);
			else
				result = llvm::ArrayType::get(result, s.mArraySize);
		}
		if (s.mReferenceLevel != 0)
			result = llvm::PointerType::get(result, 0);

		return result;
	}
}