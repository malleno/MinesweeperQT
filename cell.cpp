#include "cell.h"


Cell::Cell(int x, int y): pos_(Position{x, y}), revealed_(false){
}
Position Cell::GetPosition(){
    return pos_;
}

bool Cell::IsRevealed(){
    return revealed_;
}
void Cell::RevealCond(){
    revealed_ = true;
}
void Cell::UnrevealCond(){
    revealed_ = false;
}

bool Cell::isFlaged(){
    return !this->icon().isNull();
}

void Cell::mouseReleaseEvent(QMouseEvent *e) {
    if (e->button() == Qt::RightButton) emit rightClicked(this);
    else if (e->button() == Qt::LeftButton) emit leftClicked(this);
}
