#include "miner.h"

Miner::Miner(QWidget *parent) : QWidget(parent), width_(400), height_(400),
    columnSize_(height_/25),rowSize_(width_/25), fieldviewer_(new FieldViewer){
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
    info_layout->addWidget(new QLabel("29"),1,1);


    SetupFieldLayout();

    main_layout_ = new QVBoxLayout;
    //main_layout_ -> addWidget(pbReset);
    main_layout_ -> addLayout(info_layout);
    main_layout_ -> addLayout(layout_field_);
    SetupLayout();
    qDebug() << "MainWindow Setup done";

    fieldviewer_ -> Generate();
    qDebug() << "Field Constructed";
    qDebug() << "Miner Constructed";

}

void Miner::slotCellLeftClicked(Cell* cell){
    qDebug() << "Left click";
    RevealCell(cell);
    WinningChek();
}

void Miner::slotCellRightClicked(Cell* wd){
   ChangeCellStatus(wd);
   WinningChek();
}

void Miner::slotResetGame(){
    ResetFieldLayout();
}

void Miner::slotBomb(){
    QWidget* LossNotification = new QWidget();
    QPushButton* pbReset = new QPushButton("New Game");
    connect(pbReset, SIGNAL(clicked()), SLOT(slotResetGame()));
    connect(pbReset, SIGNAL(clicked()),LossNotification, SLOT(close()));
    QLabel* lb = new QLabel("You lose.");
    QVBoxLayout* layout = new QVBoxLayout;
    lb -> setAlignment(Qt::AlignmentFlag::AlignCenter);
    layout->addWidget(lb);
    layout->addWidget(pbReset);
    LossNotification->setLayout(layout);
    LossNotification->show();
}

void Miner::RevealCell(Cell* cell){
    if(cell->isFlaged()){
        return;
    }
    Position pos = cell->GetPosition();
    UpdateLabel(pos);
    if(fieldviewer_->IsMine(pos)){
        UpdateCellForMine(pos);
        qDebug() << "signam Bomb emited";
        emit signalBomb();
        return;
    }
    SwapCellAndLabbel(pos);
    if(fieldviewer_->IsFreeCell(pos))RevealCellArea(pos);
}

void Miner::RevealCellArea(Position pos){
    Cell* cell = nullptr;
    std::list<Position> PositionArea = GetPositionArea(pos);
    for(Position pos : PositionArea){
        cell = GetCellPtr(pos);
        if(!fieldviewer_->IsMine(pos) && !cell->IsRevealed()){
            RevealCell(cell);
        }
    }
}

void Miner::UnRevealCell(Cell* cell){
    Position pos = cell->GetPosition();
    if(cell->IsRevealed()){
         SwapCellAndLabbel(pos);
    }
}



Cell* Miner::CreateCell(Position pos){
    int cell_side = 25;
    Cell* field = new Cell(pos.x_, pos.y_);
    field->setMaximumSize(cell_side, cell_side);
    connect(field, SIGNAL(leftClicked(Cell*)), SLOT(slotCellLeftClicked(Cell*)));
    connect(field, SIGNAL(rightClicked(Cell*)), SLOT(slotCellRightClicked(Cell*)));
    return field;
}

QLabel* Miner::CreateCellLabel(){
    QLabel* lb = new QLabel();
    int cell_side = 25;
    lb->setMaximumSize(cell_side, cell_side);
    lb -> setAlignment(Qt::AlignmentFlag::AlignCenter);
    return lb;
}

Cell* Miner::GetCellPtr(Position pos){
    return cells_ptrs_.at(pos.x_).at(pos.y_);
}


void Miner::SetupFieldLayout(){
    QGridLayout* qg_layout = new QGridLayout();
    qg_layout->setContentsMargins(5,5,5,5);
    qg_layout->setSpacing(0);
    for(int i = 0; i < height_ / 25; ++i){
        for(int j = 0; j <  width_ / 25; ++j){
            Cell* cell = CreateCell(Position{j, i});
            cells_ptrs_.at(j).at(i) = cell;
            labels_ptrs_.at(j).at(i) = CreateCellLabel();
            qg_layout->addWidget(cell,j,i);

        }
    }
    layout_field_ = qg_layout;
}

void Miner::SetupLayout(){
    this->setLayout(main_layout_);
}

void Miner::ResetFieldLayout(){
    for(std::vector<Cell*> row : cells_ptrs_){
        for(Cell* cell : row){
            UnRevealCell(cell);
            if(cell->isFlaged()){
                ChangeCellStatus(cell);
            }
        }
    }
    fieldviewer_->Generate();
}


void Miner::UpdateLabel(Position pos){
    char c = fieldviewer_->GetCellValue(pos);
    if(c == 'X'){

    }else{
        UpdateLabelForNotMine(pos);
    }
}

void Miner::UpdateCellForMine(Position pos){
    cells_ptrs_.at(pos.x_).at(pos.y_)->setIcon(QIcon(":images/images/mine.png"));
}

void Miner::UpdateLabelForNotMine(Position pos){
    char c = fieldviewer_->GetCellValue(pos);
    QString cellLabel(c);
    labels_ptrs_.at(pos.x_).at(pos.y_)->setText(cellLabel);
    labels_ptrs_.at(pos.x_).at(pos.y_)->setStyleSheet("QLabel { color : "+ GetColourOfLabel(c)+"; }");
}

void Miner::SwapCellAndLabbel(Position pos){
    Cell* cell = cells_ptrs_.at(pos.x_).at(pos.y_);
    QLabel* lb = labels_ptrs_.at(pos.x_).at(pos.y_);
    if(!cell->IsRevealed()){
        layout_field_->removeWidget(cell);
        layout_field_ ->addWidget(lb, pos.x_,pos.y_);
        cell->hide();
        lb->show();
        cell->RevealCond();
    }else{
        layout_field_->removeWidget(lb);
        layout_field_ ->addWidget(cell, pos.x_,pos.y_);
        lb->hide();
        cell->show();
        cell->UnrevealCond();
    }
}

void Miner::WinningChek(){
    qDebug() << "WiningChek";
    for(int i = 0; i < height_ / 25; ++i){
        for(int j = 0; j <  width_ / 25; ++j){
            if(fieldviewer_->IsMine(Position(i,j))){
                if(!cells_ptrs_.at(i).at(j)->isFlaged()){
                    return;
                }
            }else{
                if(!cells_ptrs_.at(i).at(j)->IsRevealed()){
                    return;
                }
            }
        }
    }
    emit signalWinning();
}

void Miner::slotWinGame(){
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

void ChangeCellStatus(Cell* wd){
    if(wd->icon().isNull()){
         wd->setIcon(QIcon(":images/images/flag.png"));
    }else{
        (wd->setIcon(QIcon()));
    }
}

QString GetColourOfLabel(char c){
    std::vector<QString> colours = {"white","blue", "green", "red", "cyan",
                                    "magenta","darkRed", "darkBlue", "black"};
    int colourId = c - '0';
    return colours.at(colourId);
}

