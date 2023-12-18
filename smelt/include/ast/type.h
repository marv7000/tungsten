#pragma once
#include "shared.h"
#include <string>
#include <vector>

namespace smelt
{
	struct Type
	{
		std::string mName;
		bool mIsArray{};
		i64 mReferenceLevel{};
		i64 mArraySize = -1;
		std::vector<Type> mGenericTypes;

		Type() = default;

		explicit Type(const std::string& name, i64 ref = 0, bool array = false, i64 arraySize = -1);

		/// \brief 			Compares two Types.
		/// \param other 	The type to compare to.
		/// \return			\c true if both are equal, otherwise false.
		bool operator ==(const Type& other) const;

		std::string Mangle();
	};
}