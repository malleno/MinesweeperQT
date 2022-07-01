#include "fieldgenerator.h"

FieldGenerator::FieldGenerator(int width, int heigth):width_(width), heigth_(heigth)
{
    ResetField();
}

void FieldGenerator::Generate(){
    ResetField();
    double probabilyty;
    for(int i = 0; i < heigth_; ++i){
        for(int j = 0; j < width_; ++j){
            probabilyty = GenerateProbability();
            if(probabilyty > 0.9){
                PlaceMine(Position(j,i));
            }
        }
    }
    for(int i = 0; i < heigth_; ++i){
        for(int j = 0; j < width_; ++j){
            if(IsMine(j,i)) IncrimentArea(Position(j,i));
        }
    }
}

void FieldGenerator::PlaceMine(Position pos){
    field_.at(pos.y_).at(pos.x_) = 'X';


}
bool FieldGenerator::IsMine(int x, int y){
   return field_.at(y).at(x) == 'X';
}

void FieldGenerator::IncrimentArea(Position pos){
    //qDebug() << "IncrimentArea " <<x << " " << y;
    bool leftValid = true;
    bool upValid = true;
    bool rightValid = true;
    bool downValid = true;
    if(pos.x_ - 1 < 0) leftValid = false;
    if(pos.y_ - 1 < 0) upValid = false;
    if(pos.x_ + 1 > width_ - 1) rightValid = false;
    if(pos.y_ + 1 > heigth_ - 1) downValid = false;
    if(leftValid){
        if(!IsMine(pos.x_-1, pos.y_)) IncrimentCell(Position(pos.x_-1,pos.y_));
        if(upValid){
            if(!IsMine(pos.x_-1, pos.y_-1))IncrimentCell(Position(pos.x_-1,pos.y_-1));
        }

    }
    if(upValid){
        if(!IsMine(pos.x_, pos.y_-1)) IncrimentCell(Position(pos.x_,pos.y_-1));
        if(rightValid){
            if(!IsMine(pos.x_+1, pos.y_-1))IncrimentCell(Position(pos.x_+1,pos.y_-1));
        }
    }
    if(rightValid){
        if(!IsMine(pos.x_+1, pos.y_)) IncrimentCell(Position(pos.x_+1,pos.y_));
        if(downValid){
            if(!IsMine(pos.x_+1, pos.y_+1))IncrimentCell(Position(pos.x_+1,pos.y_+1));
        }
    }
    if(downValid){
        if(!IsMine(pos.x_, pos.y_+1)) IncrimentCell(Position(pos.x_,pos.y_+1));
        if(leftValid){
            if(!IsMine(pos.x_-1, pos.y_+1))IncrimentCell(Position(pos.x_-1,pos.y_+1));
        }
    }
}

bool FieldGenerator::IsFreeCell(int x, int y){
    return field_.at(y).at(x) == '0';
}
void FieldGenerator::IncrimentCell(Position pos){
    //qDebug() << "IncrimentCell" << x << " " << y;
    int cellValue = field_.at(pos.y_).at(pos.x_) - '0';
    //qDebug() << "Cell value: "<< field_.at(y).at(x) << " Int:"<< cellValue;
    field_.at(pos.y_).at(pos.x_) = ++cellValue + '0';
}

float FieldGenerator::GenerateProbability(){
    return std::rand()/static_cast<float>(RAND_MAX);
}

void FieldGenerator::DrawField(){
    for(int i = 0; i < heigth_; ++i){
        QString s = "";
        for(int j = 0; j < width_; ++j){
            s += field_.at(j).at(i);
            s += " ";
        }
        qDebug() << s;
    }
}

char FieldGenerator::GetCellValue(int x, int y){
    return field_.at(y).at(x);
}

void FieldGenerator::ResetField(){
    field_.resize(heigth_);
    for(int i = 0; i < heigth_; ++i){
        field_.at(i).clear();
        field_.at(i).resize(width_, '0');
    }
    srand(time(0));
}

std::vector<std::vector<char>> FieldGenerator::SendField(){
    return field_;
}
