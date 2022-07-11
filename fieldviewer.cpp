#include "fieldviewer.h"

void FieldViewer::Generate(){
    field_ = fgen_->ConstructField();
    width_ = field_[0].size();
    heigth_ = field_.size();
    CountMines();
}

FieldViewer::FieldViewer() : fgen_(new FieldGenerator(16,16)), field_(), width_(0),heigth_(0),amountOfMines_(0)
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

int FieldViewer::GetAmountOfMines(){
    return amountOfMines_;
}

void FieldViewer::CountMines(){
    amountOfMines_ = 0;
    for(int i = 0; i < heigth_; ++i){
        for(int j = 0; j < width_; ++j){
            if(IsMine(Position(j,i))){
                ++amountOfMines_;
            }
        }
    }
    qDebug() << "Amount of Mines: " << amountOfMines_;
}
