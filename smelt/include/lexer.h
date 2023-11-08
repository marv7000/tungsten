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
		std::filesystem::path mPath;
		u32 mLineNumber;
		u32 mLastColNumber;
		u32 mColNumber;
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

		/// \brief 	Advances the stream while keeping track of the line and column numbers.
		/// \return The next codepoint in the stream.
		inline i32 Next()
		{
			i32 val = mStream.get();
			if (val == '\n')
			{
				mLastColNumber = mColNumber;
				mLineNumber++;
				mColNumber = 0;
			}
			mColNumber++;
			return val;
		}

		/// \brief 	Seeks back one character in the stream and adjusts the line and column numbers.
		inline void Prev()
		{
			mStream.seekg(-1, std::ios_base::cur);
			if (mStream.peek() == '\n')
			{
				mLineNumber--;
				mColNumber = mLastColNumber + 1;
			}
			mColNumber--;
		}

		u32 GetLineNumber() const;
		u32 GetColNumber() const;

		inline std::ifstream& GetStream()
		{
			return mStream;
		}

		inline const std::filesystem::path& GetPath()
		{
			return mPath;
		}

		~Lexer();
	};
}
