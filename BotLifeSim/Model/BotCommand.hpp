#pragma once

#include <cstdint>

namespace BotLifeSim
{
	enum class BotCommand : uint64_t
	{
		Photosynthesis,
		ReadLuminanceUp,
		ReadLuminanceUpRight,
		ReadLuminanceRight,
		ReadLuminanceDownRight,
		ReadLuminanceDown,
		ReadLuminanceDownLeft,
		ReadLuminanceLeft,
		ReadLuminanceUpLeft,
		Move,
		Jump,
		LastCommand = Jump
	};
}

