#include "fieldviewer.h"
#include "fieldgenerator.h"

std::vector<Position> GetPositionArea(Position pos){
    std::vector<Position> PositionArea;
    PositionArea.push_back(Position(pos.x_-1,pos.y_-1));
    PositionArea.push_back(Position(pos.x_-1,pos.y_));
    PositionArea.push_back(Position(pos.x_-1,pos.y_+1));
    PositionArea.push_back(Position(pos.x_,pos.y_-1));
    PositionArea.push_back(Position(pos.x_,pos.y_+1));
    PositionArea.push_back(Position(pos.x_+1,pos.y_-1));
    PositionArea.push_back(Position(pos.x_+1,pos.y_));
    PositionArea.push_back(Position(pos.x_+1,pos.y_+1));
    return PositionArea;
}

bool isPositionValid(Position pos,int width, int heigth){
    bool result = true;
    result = result && (pos.x_ < 0);
    result = result && (pos.y_ < 0);
    result = result && (pos.x_ > width);
    result = result && (pos.x_ > heigth);
    return result;
}

FieldViewer::FieldViewer(std::vector<std::vector<char>> field): field_(field), width_(field[0].size()), heigth_(field.size())
{
}

char FieldViewer::GetCellValue(Position pos){
    return field_.at(pos.y_).at(pos.x_);
}

bool FieldViewer::IsMine(Position pos){
     return field_.at(pos.y_).at(pos.x_) == 'X';
}

bool FieldViewer::IsFreeCell(Position pos){
    return field_.at(pos.y_).at(pos.x_) == '0';
}
