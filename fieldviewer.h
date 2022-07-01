#pragma once
#include <vector>
#include "Position.h"

std::vector<Position> GetPositionArea(Position pos);

class FieldViewer
{
public:
    FieldViewer(std::vector<std::vector<char>> field);
    char GetCellValue(Position pos);
    bool IsMine(Position pos);
    bool IsFreeCell(Position pos);
private:
    std::vector<std::vector<char>> field_;
    int width_;
    int heigth_;
};
