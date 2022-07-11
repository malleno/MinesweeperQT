#pragma once
#include <list>

class Position
{
public:
    Position(int x, int y);
    int x_;
    int y_;
};

bool isValidPosition(Position pos);
std::list<Position> GetPositionArea(Position pos);
