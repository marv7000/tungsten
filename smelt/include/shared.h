#pragma once
#include <cstdint>

using i8 = char;
using u8 = unsigned char;
using i16 = std::int16_t;
using u16 = std::uint16_t;
using i32 = std::int32_t;
using u32 = std::uint32_t;
using i64 = std::int64_t;
using u64 = std::uint64_t;
using size = std::size_t;

#define SM_VERSION "0.1"
#define SM_LOGO R"(                     _ _   )" "\t" "\n" \
				R"(  ___ _ __ ___   ___| | |_ )" "\t" "\n" \
				R"( / __| '_ ` _ \ / _ \ | __|)" "\t" "Tungsten compiler" "\n" \
				R"( \__ \ | | | | |  __/ | |_ )" "\t" "v" SM_VERSION "\n" \
				R"( |___/_| |_| |_|\___|_|\__|)" "\t" "\n"

#define SM_PREFIX "> "
