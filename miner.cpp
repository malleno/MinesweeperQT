#include "miner.h"

Miner::Miner(QWidget *parent) :
    QWidget(parent),
    width_(400),
    height_(400),
    columnSize_(height_/25),
    rowSize_(width_/25),
    fieldviewer_(new FieldViewer)
{
    this->setWindowTitle("Miner");
    this->setMinimumSize(width_,height_);
    this->setMaximumSize(width_,height_);
    this->resize(width_,height_);
    cells_ptrs_.resize(columnSize_);
    labels_ptrs_.resize(columnSize_);
    for(int i = 0; i < columnSize_; ++i){
        cells_ptrs_.at(i).resize(rowSize_);
        labels_ptrs_.at(i).resize(rowSize_);
    }
    connect(this, SIGNAL(signalBomb()), this, SLOT(slotBomb()));
    connect(this, SIGNAL(signalWinning()), this, SLOT(slotWinGame()));

    QPushButton* pbReset = new QPushButton("Reset");
    connect(pbReset, SIGNAL(clicked()), SLOT(slotResetGame()));
    pbReset->setMaximumSize(40,40);

    QGridLayout* info_layout = new QGridLayout();
    info_layout->addWidget(pbReset,0,0);

    setupFieldLayout();

    main_layout_ = new QVBoxLayout;
    main_layout_ -> addLayout(info_layout);
    main_layout_ -> addLayout(layout_field_);
    setupLayout();
    qDebug() << "MainWindow Setup done";

    fieldviewer_ -> generateField();
    qDebug() << "Field Constructed";
    qDebug() << "Miner Constructed";
}



void Miner::slotCellLeftClicked(Cell* cell)
{
    revealCell(cell);
    winningChek();
}



void Miner::slotCellRightClicked(Cell* wd)
{
   changeCellStatus(wd);
   winningChek();
}



void Miner::slotResetGame()
{
    resetFieldLayout();
}



void Miner::slotBomb()
{
    QWidget* LossNotification = new QWidget();

    QPushButton* pbReset = new QPushButton("New Game");
    connect(pbReset, SIGNAL(clicked()), SLOT(slotResetGame()));
    connect(pbReset, SIGNAL(clicked()),LossNotification, SLOT(close()));

    QLabel* lb = new QLabel("You lose.");
    lb -> setAlignment(Qt::AlignmentFlag::AlignCenter);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(lb);
    layout->addWidget(pbReset);

    LossNotification->setLayout(layout);
    LossNotification->show();
}



void Miner::revealCell(Cell* cell)
{
    if(cell->isFlaged()){
        return;
    }

    Position pos = cell->getPosition();
    updateLabel(pos);

    if(fieldviewer_->isMine(pos)){
        updateCellForMine(pos);
        emit signalBomb();
        return;
    }

    swapCellAndLabbel(pos);
    if(fieldviewer_->isFreeCell(pos)){
        revealCellArea(pos);
    }
}



void Miner::revealCellArea(Position pos)
{
    Cell* cell = nullptr;
    std::list<Position> PositionArea = getPositionArea(pos);
    for(Position pos : PositionArea){
        cell = getCellPtr(pos);
        if(!fieldviewer_->isMine(pos) && !cell->isRevealed()){
            revealCell(cell);
        }
    }
}



void Miner::unrevealCell(Cell* cell)
{
    Position pos = cell->getPosition();
    if(cell->isRevealed()){
         swapCellAndLabbel(pos);
    }
}



Cell* Miner::createCell(Position pos)
{
    int cell_side = 25;
    Cell* field = new Cell(pos.x_, pos.y_);
    field->setMaximumSize(cell_side, cell_side);
    connect(field, SIGNAL(leftClicked(Cell*)), SLOT(slotCellLeftClicked(Cell*)));
    connect(field, SIGNAL(rightClicked(Cell*)), SLOT(slotCellRightClicked(Cell*)));
    return field;
}



QLabel* Miner::createCellLabel()
{
    QLabel* lb = new QLabel();
    int cell_side = 25;
    lb->setMaximumSize(cell_side, cell_side);
    lb -> setAlignment(Qt::AlignmentFlag::AlignCenter);
    return lb;
}



Cell* Miner::getCellPtr(Position pos){
    return cells_ptrs_.at(pos.x_).at(pos.y_);
}



void Miner::setupFieldLayout()
{
    QGridLayout* qg_layout = new QGridLayout();
    qg_layout->setContentsMargins(5,5,5,5);
    qg_layout->setSpacing(0);
    for(int i = 0; i < height_ / 25; ++i){
        for(int j = 0; j <  width_ / 25; ++j){
            Cell* cell = createCell(Position{j, i});
            cells_ptrs_.at(j).at(i) = cell;
            labels_ptrs_.at(j).at(i) = createCellLabel();
            qg_layout->addWidget(cell,j,i);

        }
    }
    layout_field_ = qg_layout;
}



void Miner::setupLayout()
{
    this->setLayout(main_layout_);
}



void Miner::resetFieldLayout()
{
    for(std::vector<Cell*> row : cells_ptrs_){
        for(Cell* cell : row){
            unrevealCell(cell);
            if(cell->isFlaged()){
                changeCellStatus(cell);
            }
        }
    }
    fieldviewer_->generateField();
}



void Miner::updateLabel(Position pos)
{
    char cellValue = fieldviewer_->getCellValue(pos);
    if(cellValue != 'X'){
        updateLabelForNotMine(pos);
    }
}



void Miner::updateCellForMine(Position pos)
{
    cells_ptrs_.at(pos.x_).at(pos.y_)->setIcon(QIcon(":images/images/mine.png"));
}



void Miner::updateLabelForNotMine(Position pos)
{
    char cellValue = fieldviewer_->getCellValue(pos);
    QString cellLabel(cellValue);
    labels_ptrs_.at(pos.x_).at(pos.y_)->setText(cellLabel);
    labels_ptrs_.at(pos.x_).at(pos.y_)->setStyleSheet("QLabel { color : "+ getColourOfLabel(cellValue)+"; }");
}



void Miner::swapCellAndLabbel(Position pos)
{
    Cell* cell = cells_ptrs_.at(pos.x_).at(pos.y_);
    QLabel* lb = labels_ptrs_.at(pos.x_).at(pos.y_);
    if(!cell->isRevealed()){
        layout_field_->removeWidget(cell);
        layout_field_ ->addWidget(lb, pos.x_,pos.y_);
        cell->hide();
        lb->show();
        cell->revealCond();
    }else{
        layout_field_->removeWidget(lb);
        layout_field_ ->addWidget(cell, pos.x_,pos.y_);
        lb->hide();
        cell->show();
        cell->unrevealCond();
    }
}



void Miner::winningChek()
{
    for(int i = 0; i < height_ / 25; ++i){
        for(int j = 0; j <  width_ / 25; ++j){
            if(fieldviewer_->isMine(Position(i,j))){
                if(!cells_ptrs_.at(i).at(j)->isFlaged()){
                    return;
                }
            }else{
                if(!cells_ptrs_.at(i).at(j)->isRevealed()){
                    return;
                }
            }
        }
    }
    emit signalWinning();
}



void Miner::slotWinGame()
{
    QWidget* LossNotification = new QWidget();
    QPushButton* pbReset = new QPushButton("New Game");
    connect(pbReset, SIGNAL(clicked()), SLOT(slotResetGame()));
    connect(pbReset, SIGNAL(clicked()),LossNotification, SLOT(close()));
    QLabel* lb = new QLabel("You win.");
    QVBoxLayout* layout = new QVBoxLayout;
    lb -> setAlignment(Qt::AlignmentFlag::AlignCenter);
    layout->addWidget(lb);
    layout->addWidget(pbReset);
    LossNotification->setLayout(layout);
    LossNotification->show();
}



void changeCellStatus(Cell* wd)
{
    if(wd->icon().isNull()){
         wd->setIcon(QIcon(":images/images/flag.png"));
    }else{
        (wd->setIcon(QIcon()));
    }
}



QString getColourOfLabel(char c)
{
    std::vector<QString> colours = {"white","blue", "green", "red", "cyan",
                                    "magenta","darkRed", "darkBlue", "black"};
    int colourId = c - '0';
    return colours.at(colourId);
}

