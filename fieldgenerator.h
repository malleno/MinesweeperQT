#pragma once
#include <vector>
#include <cstdlib>
#include <ctime>
#include <QDebug>
#include <string>
#include "Position.h"

class FieldGenerator
{
public:
    FieldGenerator() = delete;
    FieldGenerator(int width, int heigth);
    void drawField();
    std::vector<std::vector<char>> constructField();

private:
    void generateField();
    void resetField();

    void placeMine(Position pos);
    bool isMine(Position pos);
    void incrimentArea(Position pos);
    void incrimentCell(Position pos);
    float generateProbability();

private:
    std::vector<std::vector<char>> field_;
    int width_;
    int heigth_;
};

