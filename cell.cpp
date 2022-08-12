#include "cell.h"


Cell::Cell(int x, int y):
    pos_(Position{x, y}),
    revealed_(false)
{
}



Position Cell::getPosition()
{
    return pos_;
}



bool Cell::isRevealed()
{
    return revealed_;
}



void Cell::revealCond(){
    revealed_ = true;
}



void Cell::unrevealCond(){
    revealed_ = false;
}



bool Cell::isFlaged()
{
    return !this->icon().isNull();
}



void Cell::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::RightButton){
        emit rightClicked(this);
    }
    else if (e->button() == Qt::LeftButton){
        emit leftClicked(this);
    }
}
