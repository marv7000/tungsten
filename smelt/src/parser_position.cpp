#include <iostream>
#include "parser_position.h"
#include "parser.h"

namespace smelt
{
	ParserPosition::ParserPosition(Parser *parser)
	{
		mPath = parser->mLexer->GetPath();
		mLine = parser->mLexer->GetTokenLineNumber();
		mCol = parser->mLexer->GetTokenColNumber();
		mLineStr = parser->GetLine(mLine);
	}

	ParserPosition::ParserPosition(const std::string &file, u32 line, u32 col)
	{
		mPath = file;
		mLine = line;
		mCol = col;
	}

	std::string ParserPosition::String()
	{
		std::stringstream s;
		s << canonical(mPath).string() << ":" << mLine << ":" << mCol;
		return s.str();
	}

	void ParserPosition::Error()
	{
		std::cerr << "Error: " << canonical(mPath).string() << ":" << mLine << ":" << mCol << "\n";
		// Show which token is incorrect.
		std::cerr << mLine << "\t| " << mLineStr << "\n\t| ";

		for (i32 i = 1; i < mCol; i++)
		{
			std::cerr << " ";
		}

		std::cerr << "^ ";
	}
}
