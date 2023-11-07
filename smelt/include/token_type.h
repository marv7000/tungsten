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

		LiString,
		LiChar,
		LiInt,
		LiFloat,
		LiDouble,
		LiBool
	};
}
