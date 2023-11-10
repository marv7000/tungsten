#pragma once
#include "parser.h"

namespace smelt
{
	/// \brief 	Represents an interface for a node in the abstract syntax tree.
	class INode
	{
	public:
		ParserPosition mPosition;
		virtual ~INode() = default;
	};
}
