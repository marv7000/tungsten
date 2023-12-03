#pragma once
#include <filesystem>
#include "shared.h"

namespace smelt
{
	class Parser;

	struct ParserPosition
	{
		std::filesystem::path mPath;
		u32 mLine{};
		u32 mCol{};
		std::string mLineStr;

		ParserPosition() = default;
		ParserPosition(const std::string& file, u32 line, u32 col);
		explicit ParserPosition(Parser* parser);

		std::string String();
		void Error();
	};

}