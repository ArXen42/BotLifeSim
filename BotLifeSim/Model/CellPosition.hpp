#pragma once

#include <stdint-gcc.h>
#include <ostream>

namespace BotLifeSim
{
	class CellPosition
	{
	public:
		uint64_t X;
		uint64_t Y;

		bool operator==(const CellPosition& rhs) const
		{
			return X == rhs.X &&
			       Y == rhs.Y;
		}

		bool operator!=(const CellPosition& rhs) const
		{
			return !(rhs == *this);
		}
	};

	std::ostream& operator<<(std::ostream& os, CellPosition const& cellPosition);
}



