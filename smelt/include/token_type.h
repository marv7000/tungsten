#pragma once

namespace smelt
{
	enum class TokenType
	{
		Eof = -1,

		Identifier,

		SySemicolon,
		SyComma,
		SyDot,
		SyQuestionMark,
		SyExclamMark,
		SyPlus,
		SyMinus,
		SyAsterisk,
		SySlash,
		SyBackSlash,
		SyAmp,
		SyPercent,
		SyEqual,
		SyCaret,
		SyLess,
		SyMore,

		BrOpRound,
		BrClRound,
		BrOpSquare,
		BrClSquare,
		BrOpCurly,
		BrClCurly,

		KwInclude,
		KwNamespace,
		KwReturn,
		KwStruct,
		KwHeap,
		KwStack,
		KwMain,

		LiString = 1 << 5,
		LiChar = 1 << 6,
		LiInt = 1 << 7,
		LiFloat = 1 << 8,
		LiDouble = 1 << 9,
		LiBool = 1 << 10,
		LiNum = LiChar | LiInt | LiFloat | LiDouble | LiBool,
		LiAll = LiString | LiChar | LiInt | LiFloat | LiDouble | LiBool,
	};
}
