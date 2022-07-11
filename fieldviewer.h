#pragma once
#include <vector>
#include "Position.h"
#include "fieldgenerator.h"

class FieldViewer
{
public:
    FieldViewer();
    void Generate();
    char GetCellValue(Position pos);
    bool IsMine(Position pos);
    bool IsFreeCell(Position pos);
    int GetAmountOfMines();
private:
    FieldGenerator* fgen_;
    std::vector<std::vector<char>> field_;
    int width_;
    int heigth_;
    int amountOfMines_;

    void CountMines();
};
