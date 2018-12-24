// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "CellInfo.hpp"
#include "World.hpp"


BotLifeSim::CellInfo::CellInfo(BotLifeSim::World* world, const BotLifeSim::CellPosition& position, const BotLifeSim::EnergyT luminance)
		: _world(world),
		  _position(position),
		  _luminance(luminance),
		  _bot(nullptr)
{}

BotLifeSim::CellInfo* const BotLifeSim::CellInfo::GetCellUp() const
{ return _world->GetCellInfo(_position.X, _position.Y - 1); }

BotLifeSim::CellInfo* const BotLifeSim::CellInfo::GetCellUpRight() const
{ return _world->GetCellInfo(_position.X + 1, _position.Y - 1); }

BotLifeSim::CellInfo* const BotLifeSim::CellInfo::GetCellRight() const
{ return _world->GetCellInfo(_position.X + 1, _position.Y); }

BotLifeSim::CellInfo* const BotLifeSim::CellInfo::GetCellDownRight() const
{ return _world->GetCellInfo(_position.X + 1, _position.Y + 1); }

BotLifeSim::CellInfo* const BotLifeSim::CellInfo::GetCellDown() const
{ return _world->GetCellInfo(_position.X, _position.Y + 1); }

BotLifeSim::CellInfo* const BotLifeSim::CellInfo::GetCellDownLeft() const
{ return _world->GetCellInfo(_position.X - 1, _position.Y + 1); }

BotLifeSim::CellInfo* const BotLifeSim::CellInfo::GetCellLeft() const
{ return _world->GetCellInfo(_position.X - 1, _position.Y); }

BotLifeSim::CellInfo* const BotLifeSim::CellInfo::GetCellUpLeft() const
{ return _world->GetCellInfo(_position.X - 1, _position.Y - 1); }
