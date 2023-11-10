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
		bool mIsArray{};
		bool mIsReference{};
		i64 mArraySize = -1;
		std::vector<Type> mGenericTypes;

		inline Type() = default;

		inline explicit Type(const std::string& name, bool ref = false, bool array = false, i64 arraySize = -1)
		{
			mName = name;
			mIsReference = ref;
			mIsArray = array;
			mArraySize = arraySize;
		}

		/// \brief 			Compares two Types.
		/// \param other 	The type to compare to.
		/// \return			\c true if both are equal, otherwise false.
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

		inline bool IsBuiltIn() const
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

		inline std::string Mangle() const
		{
			std::stringstream s;
			s << mNamespace << "::" << mName << "::";
			if (!mGenericTypes.empty())
			{
				s << "+" << mGenericTypes.size();
			}
			return s.str();
		}
	};

	struct NamedType
	{
		Type mType;
		std::string mName;
	};
}