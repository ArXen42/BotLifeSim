// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "CellInfo.hpp"
#include "World.hpp"


BotLifeSim::CellInfo::CellInfo(BotLifeSim::World* _world, const BotLifeSim::CellPosition& _position,
                               BotLifeSim::EnergyT _luminance) : _world(_world), _position(_position),
                                                                 _luminance(_luminance)
{}

BotLifeSim::CellInfo BotLifeSim::CellInfo::GetCellUp() const
{ return _world->GetCellInfo(_position.X, _position.Y - 1); }

BotLifeSim::CellInfo BotLifeSim::CellInfo::GetCellUpRight() const
{ return _world->GetCellInfo(_position.X + 1, _position.Y - 1); }

BotLifeSim::CellInfo BotLifeSim::CellInfo::GetCellRight() const
{ return _world->GetCellInfo(_position.X + 1, _position.Y); }

BotLifeSim::CellInfo BotLifeSim::CellInfo::GetCellDownRight() const
{ return _world->GetCellInfo(_position.X + 1, _position.Y + 1); }

BotLifeSim::CellInfo BotLifeSim::CellInfo::GetCellDown() const
{ return _world->GetCellInfo(_position.X, _position.Y + 1); }

BotLifeSim::CellInfo BotLifeSim::CellInfo::GetCellDownLeft() const
{ return _world->GetCellInfo(_position.X - 1, _position.Y + 1); }

BotLifeSim::CellInfo BotLifeSim::CellInfo::GetCellLeft() const
{ return _world->GetCellInfo(_position.X - 1, _position.Y); }

BotLifeSim::CellInfo BotLifeSim::CellInfo::GetCellUpLeft() const
{ return _world->GetCellInfo(_position.X - 1, _position.Y - 1); }

bool BotLifeSim::CellInfo::IsFilled() const
{
	return _world->IsCellFilled(_position.X, _position.Y);
}
