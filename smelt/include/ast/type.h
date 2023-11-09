#pragma once
#include "shared.h"
#include <string>
#include <vector>

namespace smelt
{
	struct Type
	{
		std::string mNamespace;
		std::string mName;
		bool mIsArray;
		bool mIsReference;
		i64 mArraySize = -1;
		std::vector<Type> mGenericTypes;

		inline bool operator ==(const Type& other) const
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
	};
}