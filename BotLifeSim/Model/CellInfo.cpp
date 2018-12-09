#include "CellInfo.hpp"
#include "World.hpp"


BotLifeSim::CellInfo::CellInfo(BotLifeSim::World* _world, const BotLifeSim::CellPosition& _position,
                               BotLifeSim::EnergyT _luminance) : _world(_world), _position(_position),
                                                                 _luminance(_luminance)
{}

BotLifeSim::CellInfo BotLifeSim::CellInfo::GetCellUp()
{ return _world->GetCellInfo(_position.X, _position.Y - 1); }

BotLifeSim::CellInfo BotLifeSim::CellInfo::GetCellUpRight()
{ return _world->GetCellInfo(_position.X + 1, _position.Y - 1); }

BotLifeSim::CellInfo BotLifeSim::CellInfo::GetCellRight()
{ return _world->GetCellInfo(_position.X + 1, _position.Y); }

BotLifeSim::CellInfo BotLifeSim::CellInfo::GetCellDownRight()
{ return _world->GetCellInfo(_position.X + 1, _position.Y + 1); }

BotLifeSim::CellInfo BotLifeSim::CellInfo::GetCellDown()
{ return _world->GetCellInfo(_position.X, _position.Y + 1); }

BotLifeSim::CellInfo BotLifeSim::CellInfo::GetCellDownLeft()
{ return _world->GetCellInfo(_position.X - 1, _position.Y + 1); }

BotLifeSim::CellInfo BotLifeSim::CellInfo::GetCellLeft()
{ return _world->GetCellInfo(_position.X - 1, _position.Y); }

BotLifeSim::CellInfo BotLifeSim::CellInfo::GetCellLeftUp()
{ return _world->GetCellInfo(_position.X - 1, _position.Y - 1); }
