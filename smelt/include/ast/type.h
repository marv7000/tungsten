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

		Type() = default;

		explicit Type(const std::string& name, bool ref = false, bool array = false, i64 arraySize = -1);

		/// \brief 			Compares two Types.
		/// \param other 	The type to compare to.
		/// \return			\c true if both are equal, otherwise false.
		bool operator ==(const Type& other) const;

		std::string Mangle();
	};
}