#include "fieldgenerator.h"

FieldGenerator::FieldGenerator(int width, int heigth):width_(width), heigth_(heigth)
{
    ResetField();
}

void FieldGenerator::Generate(){
    srand(time(0));
    ResetField();
    double probabilyty;
    for(int i = 0; i < heigth_; ++i){
        for(int j = 0; j < width_; ++j){
            probabilyty = GenerateProbability();
            if(probabilyty > 0.85){
                PlaceMine(Position(j,i));
            }
        }
    }
    for(int i = 0; i < heigth_; ++i){
        for(int j = 0; j < width_; ++j){
            if(IsMine(Position(j,i))) IncrimentArea(Position(j,i));
        }
    }
    DrawField();
}

void FieldGenerator::PlaceMine(Position pos){
    field_.at(pos.y_).at(pos.x_) = 'X';


}
bool FieldGenerator::IsMine(Position pos){
   return field_.at(pos.y_).at(pos.x_) == 'X';
}

void FieldGenerator::IncrimentArea(Position pos){
    std::list<Position> PositionArea = GetPositionArea(pos);
    for(Position pos : PositionArea){
        if(!IsMine(pos)){
            IncrimentCell(pos);
        }
    }
}

void FieldGenerator::IncrimentCell(Position pos){
    int cellValue = field_.at(pos.y_).at(pos.x_) - '0';
    field_.at(pos.y_).at(pos.x_) = ++cellValue + '0';
}

float FieldGenerator::GenerateProbability(){
    return std::rand()/static_cast<float>(RAND_MAX);
}

void FieldGenerator::DrawField(){
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

void FieldGenerator::ResetField(){
    field_.resize(heigth_);
    for(int i = 0; i < heigth_; ++i){
        field_.at(i).clear();
        field_.at(i).resize(width_, '0');
    }
    srand(time(0));
}

std::vector<std::vector<char>> FieldGenerator::ConstructField(){
    Generate();
    return field_;
}
