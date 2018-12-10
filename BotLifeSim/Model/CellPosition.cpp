// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "CellPosition.hpp"

std::ostream& BotLifeSim::operator<<(std::ostream& os, const BotLifeSim::CellPosition& cellPosition)
{
	return os << cellPosition.X << " " << cellPosition.Y;
}
