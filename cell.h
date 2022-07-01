#pragma once
#include <QPushButton>
#include "Position.h"
#include <QMouseEvent>

class Cell : public QPushButton
{
    Q_OBJECT
public:
    Cell() = delete;
    Cell(int x, int y);
    Position GetPosition();
    bool IsRevealed();
    void RevealCond();
    void UnrevealCond();
signals:
    void ClickedP(Cell* p);
    void rightClicked(Cell* p);
private:
    Position pos_;
    bool revealed_;
    void mouseReleaseEvent(QMouseEvent *e);
};

