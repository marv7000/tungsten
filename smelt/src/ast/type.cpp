#include "ast/type.h"
#include <sstream>

namespace smelt
{
	std::string Type::Mangle()
	{
		std::stringstream s;
		s << mNamespace << "::" << mName << "::";
		if (!mGenericTypes.empty())
		{
			s << "+" << mGenericTypes.size();
		}
		return s.str();
	}

	bool Type::operator==(const Type &other) const
	{
		bool cmp = (mNamespace == other.mNamespace &&
		            mName == other.mName &&
		            mIsArray == other.mIsArray &&
		            mIsReference == other.mIsReference &&
		            mArraySize == other.mArraySize);

		if (mGenericTypes.size() != other.mGenericTypes.size())
			return false;
		// Recursively traverse all generics.
		for (i64 i = 0; i < mGenericTypes.size(); i++)
		{
			cmp &= (mGenericTypes[i] == other.mGenericTypes[i]);
		}
		return cmp;
	}

	Type::Type(const std::string &name, bool ref, bool array, i64 arraySize)
	{
		mName = name;
		mIsReference = ref;
		mIsArray = array;
		mArraySize = arraySize;
	}

	bool Type::IsBuiltIn() const
	{
		if (!mNamespace.empty())
			return false;

		if (mName != "i8" &&
		    mName != "u8" &&
		    mName != "i16" &&
		    mName != "u16" &&
		    mName != "i32" &&
		    mName != "u32" &&
		    mName != "i64" &&
		    mName != "u64" &&
		    mName != "isize" &&
		    mName != "usize" &&
		    mName != "float" &&
		    mName != "double" &&
		    mName != "bool" &&
		    mName != "void"
				)
			return false;

		return true;
	}
}