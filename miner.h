#pragma once
#include "cell.h"
#include "fieldgenerator.h"
#include "fieldviewer.h"
#include <QtWidgets>
#include "Position.h"
#include <QDebug>
class Miner : public QWidget
{
    Q_OBJECT

public:
    Miner(QWidget *parent = nullptr);

public slots:
    void slotCellLeftClicked(Cell* wd);
    void slotCellRightClicked(Cell* wd);
    void slotResetGame();
    void slotWinGame();
    void slotBomb();

signals:
    void signalBomb();
    void signalWinning();

private:
    Cell* createCell(Position pos);
    QLabel* createCellLabel();
    Cell* getCellPtr(Position pos);

    void setupLayout();
    void setupFieldLayout();
    void resetFieldLayout();

    void revealCell(Cell*);
    void revealCellArea(Position pos);
    void unrevealCell(Cell*);
    void updateLabel(Position pos);
    void updateCellForMine(Position pos);
    void updateLabelForNotMine(Position pos);
    void swapCellAndLabbel(Position pos);

    void winningChek();

private:
    int width_;              //Field Size in px
    int height_;
    int columnSize_;         //Cells in column and row
    int rowSize_;
    std::vector<std::vector<Cell*>>   cells_ptrs_;
    std::vector<std::vector<QLabel*>> labels_ptrs_;
    FieldViewer* fieldviewer_;
    QVBoxLayout* main_layout_;
    QGridLayout* layout_field_;

};
    void changeCellStatus(Cell* wd);
    QString getColourOfLabel(char c);


