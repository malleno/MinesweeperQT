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
    Position getPosition();
    bool isRevealed();
    void revealCond();
    void unrevealCond();
    bool isFlaged();

private:
    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void leftClicked(Cell* p);
    void rightClicked(Cell* p);

private:
    Position pos_;
    bool revealed_;
};

