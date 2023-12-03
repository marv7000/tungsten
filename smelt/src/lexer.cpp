#include "lexer.h"

namespace smelt
{
	Lexer::Lexer(const std::filesystem::path& path)
	{
		mStream = std::ifstream(path);
		mLineNumber = 1;
		mColNumber = 1;
		mLastColNumber = 1;
		mTokenStartLine = 1;
		mTokenStartCol = 1;
		mPath = path;
	}

	TokenType Lexer::GetToken(bool peek)
	{
		mLastChar = ' ';
		if (!peek)
		{
			mTokenStartLine = GetLineNumber();
			mTokenStartCol = GetColNumber();
		}

		// Ignore whitespace.
		while (isspace(mLastChar))
		{
			mLastChar = Next();
			if (mStream.fail())
				return TokenType::Eof;
		}

		// Comments.
		if (mLastChar == '/')
		{
			mLastChar = Next();
			// Single line.
			if (mLastChar == '/')
			{
				while (mLastChar != EOF && mLastChar != '\n' && mLastChar != '\r')
				{
					mLastChar = Next();
				}
				if (mLastChar != EOF)
					return GetToken(peek);
			}
			// Multi line.
			else if (mLastChar == '*')
			{
				while (mLastChar != EOF)
				{
					mLastChar = Next();
					if (mLastChar == '*')
					{
						mLastChar = Next();
						if (mLastChar == '/')
							return GetToken(peek);
					}
				}
				// TODO: Handle syntax error.
				exit(1);
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
			case '&': return TokenType::SyAmp;
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
			mLastChar = Next();
			while (isalnum(mLastChar) || mLastChar == '_')
			{
				mLastIdentifier += (char)mLastChar;
				mLastChar = Next();
			}
			// Seek back one char.
			Prev();

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
			if (mLastIdentifier == "true" || mLastIdentifier == "false")
			{
				mLastLiteral = mLastIdentifier;
				return TokenType::LiBool;
			}
		}

		// String literal.
		if (mLastChar == '"')
		{
			mLastLiteral = "";
			while ((mLastChar = Next()) != EOF)
			{
				if (mLastChar == '"')
					break;
				if (mLastChar == '\\')
				{
					mLastChar = Next();
					switch (mLastChar)
					{
						case 'n':
							mLastChar = '\n'; break;
						case 'r':
							mLastChar = '\r'; break;
						case 't':
							mLastChar = '\t'; break;
						case '\\':
							mLastChar = '\\'; break;
						case '"':
							mLastChar = '"'; break;
						default:
							return TokenType::LiChar;
					}
				}
				mLastLiteral += (char)mLastChar;
			}
			return TokenType::LiString;
		}
		// Character literal.
		if (mLastChar == '\'')
		{
			mLastChar = Next();
			while (mLastChar != '\'')
			{
				mLastChar = Next();
			}
			return TokenType::LiChar;
		}
		// Number literals.
		if (isdigit(mLastChar))
		{
			// Parse the literal.
			mLastLiteral = (char)mLastChar;
			while (isdigit(mLastChar = Next()) ||
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
			Prev();

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

	u32 Lexer::GetLineNumber() const
	{
		return mLineNumber;
	}

	u32 Lexer::GetColNumber() const
	{
		return mColNumber;
	}

	u32 Lexer::GetTokenLineNumber() const
	{
		return mTokenStartLine;
	}

	u32 Lexer::GetTokenColNumber() const
	{
		return mTokenStartCol;
	}
}
