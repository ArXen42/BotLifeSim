#pragma once

#include <stdint-gcc.h>
#include <ostream>

namespace BotLifeSim
{
	class CellPosition
	{
	public:
		int64_t X;
		int64_t Y;

		bool operator==(const CellPosition& rhs) const
		{
			return X == rhs.X &&
			       Y == rhs.Y;
		}

		bool operator!=(const CellPosition& rhs) const
		{
			return !(rhs == *this);
		}

		void FitConstraints(int64_t xMax, int64_t yMax)
		{
			X %= xMax;
			Y %= yMax;

			if (X < 0)
				X = xMax - X;
			if (Y < 0)
				Y = 0;
		}
	};

	std::ostream& operator<<(std::ostream& os, CellPosition const& cellPosition);
}



