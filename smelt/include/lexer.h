#pragma once
#include "token_type.h"
#include "shared.h"

#include <string>
#include <fstream>
#include <filesystem>

namespace smelt
{
	/// \brief 	Breaks up a file of source code into tokens.
	class Lexer
	{
		std::string mLastIdentifier{};
		std::string mLastLiteral{};
		i32 mLastChar = ' ';
		std::ifstream mStream;
	public:
		/// \brief 		Instantiates a new lexer over a file.
		/// \param path The path to the file.
		explicit Lexer(const std::filesystem::path& path);

		/// \brief 	Get the next token in the current file.
		/// \return	The evaluated token, or \c TokenType::Unknown if it failed.
		TokenType GetToken();

		/// \brief 	Gets the last scanned identifier.
		/// \return The last identifier.
		const std::string& GetIdentifier() const;

		/// \brief 	Gets the last scanned literal.
		/// \return The last literal.
		const std::string& GetLiteral() const;

		~Lexer();
	};
}
