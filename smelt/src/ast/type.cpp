#include "ast/type.h"
#include <sstream>

namespace smelt
{
	std::string Type::Mangle()
	{
		std::stringstream s;
		if (!mGenericTypes.empty())
		{
			s << "+" << mGenericTypes.size();
		}
		return s.str();
	}

	bool Type::operator==(const Type &other) const
	{
		bool cmp = (mName == other.mName &&
		            mIsArray == other.mIsArray &&
		            mReferenceLevel == other.mReferenceLevel &&
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

	Type::Type(const std::string &name, i64 ref, bool array, i64 arraySize)
	{
		mName = name;
		mReferenceLevel = ref;
		mIsArray = array;
		mArraySize = arraySize;
	}
}