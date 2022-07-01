#pragma once
#include "cell.h"
#include "fieldgenerator.h"
#include <QtWidgets>
#include "Position.h"
#include <QDebug>
class Miner : public QWidget
{
    Q_OBJECT

public:
    Miner(QWidget *parent = nullptr);
public slots:
    void slotCellClicked(Cell* wd);
    void slotResetGame();
    void slotBomb();
signals:
    void signalBomb();
private:
    int width_;              //Field Size in px
    int height_;
    const int cell_side_;
    int columnSize_;         //Mines in column and row
    int rowSize_;
    std::vector<std::vector<Cell*>> cells_ptrs_;
    std::vector<std::vector<QLabel*>> labels_ptrs_;
    FieldGenerator fgen_;
    QVBoxLayout* main_layout_;
    QGridLayout* layout_field_;

    Cell* CreateCell(Position pos);
    QLabel* CreateCellLabel();
    Cell* GetCellPtr(Position pos);
    void SetupLayout();
    void SetupFieldLayout();
    void ResetFieldLayout();
    void RevealCell(Cell*);
    void UnRevealCell(Cell*);

    void RevealCellArea(Position pos);
    void UpdateLabel(Position pos);
    void SwapCellAndLabbel(Position pos);
};


