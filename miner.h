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
    int width_;              //Field Size in px
    int height_;
    int columnSize_;         //Mines in column and row
    int rowSize_;
    std::vector<std::vector<Cell*>> cells_ptrs_;
    std::vector<std::vector<QLabel*>> labels_ptrs_;
    FieldViewer* fieldviewer_;
    QVBoxLayout* main_layout_;
    QGridLayout* layout_field_;

    Cell* CreateCell(Position pos);
    QLabel* CreateCellLabel();
    Cell* GetCellPtr(Position pos);

    void SetupLayout();
    void SetupFieldLayout();
    void ResetFieldLayout();

    void RevealCell(Cell*);
    void RevealCellArea(Position pos);
    void UnRevealCell(Cell*);
    void UpdateLabel(Position pos);
    void UpdateCellForMine(Position pos);
    void UpdateLabelForNotMine(Position pos);
    void SwapCellAndLabbel(Position pos);

    void WinningChek();
};
    void ChangeCellStatus(Cell* wd);
    QString GetColourOfLabel(char c);


