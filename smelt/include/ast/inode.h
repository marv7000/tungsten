#pragma once
#include "parser_position.h"

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
