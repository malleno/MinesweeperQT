#pragma once
#include <vector>
#include "Position.h"
#include "fieldgenerator.h"

class FieldViewer
{
public:
    FieldViewer();
    void generateField();
    char getCellValue(Position pos);
    bool isMine(Position pos);
    bool isFreeCell(Position pos);
    int  getAmountOfMines();

private:
    void countMines();

private:
    FieldGenerator* fgen_;
    std::vector<std::vector<char>> field_;
    int width_;
    int heigth_;
    int amountOfMines_;
};
