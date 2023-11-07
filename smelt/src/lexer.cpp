#include "lexer.h"

namespace smelt
{
	Lexer::Lexer(const std::filesystem::path& path)
	{
		mStream = std::ifstream(path);
	}

	TokenType Lexer::GetToken()
	{
		mLastChar = ' ';

		// Ignore whitespace.
		while (isspace(mLastChar))
		{
			mLastChar = mStream.get();
			if (mStream.fail())
				return TokenType::Eof;
		}

		// Comments.
		if (mLastChar == '/')
		{
			mLastChar = mStream.get();
			if (mLastChar == '/')
			{
				while (mLastChar != EOF && mLastChar != '\n' && mLastChar != '\r')
				{
					mLastChar = mStream.get();
				}
				if (mLastChar != EOF)
					return GetToken();
			}
			return TokenType::SySlash;
		}

		// Symbols and braces.
		switch (mLastChar)
		{
			case ';': return TokenType::SySemicolon;
			case ',': return TokenType::SyComma;
			case '.': return TokenType::SyDot;
			case '?': return TokenType::SyQuestionMark;
			case '!': return TokenType::SyExclamMark;
			case '+': return TokenType::SyPlus;
			case '-': return TokenType::SyMinus;
			case '*': return TokenType::SyAsterisk;
			case '\\': return TokenType::SyBackSlash;
			case '%': return TokenType::SyPercent;
			case '=': return TokenType::SyEqual;
			case '^': return TokenType::SyCaret;
			case '<': return TokenType::SyLess;
			case '>': return TokenType::SyMore;

			case '(': return TokenType::BrOpRound;
			case ')': return TokenType::BrClRound;
			case '[': return TokenType::BrOpSquare;
			case ']': return TokenType::BrClSquare;
			case '{': return TokenType::BrOpCurly;
			case '}': return TokenType::BrClCurly;
		}

		// Alphanumeric tokens.
		if (isalpha(mLastChar))
		{
			mLastIdentifier = (char)mLastChar;
			while (isalnum(mLastChar = mStream.get()))
			{
				mLastIdentifier += (char)mLastChar;
			}
			// Seek back one char.
			mStream.seekg(-1, std::ios_base::cur);

			if (mLastIdentifier == "include")
				return TokenType::KwInclude;
			if (mLastIdentifier == "namespace")
				return TokenType::KwNamespace;
			if (mLastIdentifier == "return")
				return TokenType::KwReturn;
			if (mLastIdentifier == "struct")
				return TokenType::KwStruct;
			if (mLastIdentifier == "heap")
				return TokenType::KwHeap;
			if (mLastIdentifier == "stack")
				return TokenType::KwStack;
			if (mLastIdentifier == "main")
				return TokenType::KwMain;
			if (mLastIdentifier == "true" || mLastIdentifier == "false")
				return TokenType::LiBool;
		}

		// String literal.
		if (mLastChar == '"')
		{
			mLastLiteral = "";
			while ((mLastChar = mStream.get()) != '"')
			{
				mLastLiteral += (char)mLastChar;
			}
			return TokenType::LiString;
		}
		// Character literal.
		if (mLastChar == '\'')
		{
			mLastChar = mStream.get();
			while (mLastChar != '\'')
			{
				mLastChar = mStream.get();
			}
			return TokenType::LiChar;
		}
		// Number literals.
		if (isdigit(mLastChar))
		{
			// Parse the literal.
			mLastLiteral = (char)mLastChar;
			while (isdigit(mLastChar = mStream.get()) ||
				mLastChar == '.' || mLastChar == '-' || // Decimal point and sign.
				mLastChar == 'f' || mLastChar == 'F' || // Float suffix.
				mLastChar == 'x' || mLastChar == 'X' || // Hex literals.
				mLastChar == 'b' || mLastChar == 'B' || // Binary literals.
				mLastChar == '_' // Visual separators.
				)
			{
				mLastLiteral += (char)mLastChar;
			}
			// Seek back one char.
			mStream.seekg(-1, std::ios_base::cur);

			// Decimals
			if (mLastLiteral.find('.') != std::string::npos)
			{
				if (mLastLiteral.ends_with('f') || mLastLiteral.ends_with('F'))
					return TokenType::LiFloat;
				return TokenType::LiDouble;
			}
			return TokenType::LiInt;
		}

		// Unhandled case, so assume we have an identifier token.
		return TokenType::Identifier;
	}

	const std::string& Lexer::GetIdentifier() const
	{
		return mLastIdentifier;
	}

	const std::string& Lexer::GetLiteral() const
	{
		return mLastLiteral;
	}

	Lexer::~Lexer()
	{
		mStream.close();
	}
}
