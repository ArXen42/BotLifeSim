#include "CellPosition.hpp"

std::ostream& BotLifeSim::operator<<(std::ostream& os, const BotLifeSim::CellPosition& cellPosition)
{
	return os << cellPosition.X << " " << cellPosition.Y;
}
