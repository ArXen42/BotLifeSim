#pragma once

#include <cstdint>

namespace BotLifeSim
{

	class Bot
	{
	public:
		Bot(int64_t x, int64_t y) :
				_x(x),
				_y(y)
		{}

		int64_t GetX() const
		{ return _x; }

		int64_t GetY() const
		{ return _y; }

	private:
		int64_t _x, _y;
	};
}
