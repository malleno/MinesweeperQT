#include "fieldgenerator.h"

FieldGenerator::FieldGenerator(int width, int heigth):
    width_(width),
    heigth_(heigth)
{
}



void FieldGenerator::generateField()
{
    srand(time(0));
    resetField();
    double probabilyty;
    for(int i = 0; i < heigth_; ++i){
        for(int j = 0; j < width_; ++j){
            probabilyty = generateProbability();
            if(probabilyty > 0.85){
                placeMine (Position(j,i));
            }
        }
    }
    for(int i = 0; i < heigth_; ++i){
        for(int j = 0; j < width_; ++j){
            if(isMine (Position(j,i))){
                incrimentArea (Position(j,i));
            }
        }
    }
    drawField();
}



void FieldGenerator::placeMine(Position pos)
{
    field_.at(pos.y_).at(pos.x_) = 'X';
}



bool FieldGenerator::isMine(Position pos)
{
   return field_.at(pos.y_).at(pos.x_) == 'X';
}



void FieldGenerator::incrimentArea(Position pos)
{
    std::list<Position> PositionArea = getPositionArea(pos);
    for(Position pos : PositionArea){
        if(!isMine(pos)){
            incrimentCell(pos);
        }
    }
}

void FieldGenerator::incrimentCell(Position pos)
{
    int cellValue = field_.at(pos.y_).at(pos.x_) - '0';
    field_.at(pos.y_).at(pos.x_) = ++cellValue + '0';
}



float FieldGenerator::generateProbability()
{
    return std::rand()/static_cast<float>(RAND_MAX);
}



void FieldGenerator::drawField()
{
    qDebug() << "__FIELD__";
    for(int i = 0; i < heigth_; ++i){
        QString s = "";
        for(int j = 0; j < width_; ++j){
            s += field_.at(j).at(i);
            s += " ";
        }
        qDebug() << s;
    }
    qDebug() << "__END_FIELD__";
}



void FieldGenerator::resetField()
{
    field_.resize(heigth_);
    for(int i = 0; i < heigth_; ++i){
        field_.at(i).clear();
        field_.at(i).resize(width_, '0');
    }
    srand(time(0));
}



std::vector<std::vector<char>> FieldGenerator::constructField()
{
    generateField();
    return field_;
}
