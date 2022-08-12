#include "fieldviewer.h"


FieldViewer::FieldViewer() :
    fgen_(new FieldGenerator(16,16)),
    field_(),
    width_(0),
    heigth_(0),
    amountOfMines_(0)
{
}



void FieldViewer::generateField()
{
    field_ = fgen_->constructField();
    width_ = field_[0].size();
    heigth_ = field_.size();
    countMines();
}



char FieldViewer::getCellValue(Position pos)
{
    return field_.at(pos.y_).at(pos.x_);
}



bool FieldViewer::isMine(Position pos)
{
     return field_.at(pos.y_).at(pos.x_) == 'X';
}



bool FieldViewer::isFreeCell(Position pos)
{
    return field_.at(pos.y_).at(pos.x_) == '0';
}



int FieldViewer::getAmountOfMines()
{
    return amountOfMines_;
}



void FieldViewer::countMines()
{
    amountOfMines_ = 0;
    for(int i = 0; i < heigth_; ++i){
        for(int j = 0; j < width_; ++j){
            if(isMine(Position(j,i))){
                ++amountOfMines_;
            }
        }
    }
}
