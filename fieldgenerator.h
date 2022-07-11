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
    void Generate();
    void DrawField();
    std::vector<std::vector<char>> ConstructField();
    bool IsMine(Position pos);

private:
    std::vector<std::vector<char>> field_;
    int width_;
    int heigth_;

    void PlaceMine(Position pos);
    void ResetField();
    void IncrimentArea(Position pos);
    void IncrimentCell(Position pos);
    float GenerateProbability();
};

