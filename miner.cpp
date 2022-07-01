#include "miner.h"

Miner::Miner(QWidget *parent) : QWidget(parent), width_(400), height_(400), cell_side_(25),
    columnSize_(height_/cell_side_),rowSize_(width_/cell_side_), fgen_(columnSize_,rowSize_){
    this->setWindowTitle("Miner");
    this->setMinimumSize(width_,height_);
    this->resize(width_,height_);
    cells_ptrs_.resize(columnSize_);
    labels_ptrs_.resize(columnSize_);
    for(int i = 0; i < columnSize_; ++i){
        cells_ptrs_.at(i).resize(rowSize_);
        labels_ptrs_.at(i).resize(rowSize_);
    }
    connect(this, SIGNAL(signalBomb()), this, SLOT(slotBomb()));

    QPushButton* pbReset = new QPushButton("Reset");
    connect(pbReset, SIGNAL(clicked()), SLOT(slotResetGame()));
    pbReset->resize(20,20);

    SetupFieldLayout();

    main_layout_ = new QVBoxLayout;
    main_layout_ -> addWidget(pbReset);
    main_layout_ -> addLayout(layout_field_);
    SetupLayout();
    qDebug() << "MainWindow Setup done";

    fgen_.Generate();
    fgen_.DrawField();
    qDebug() << "Field Constructed";
    qDebug() << "Miner Constructed";

}

void Miner::slotCellClicked(Cell* cell){
    RevealCell(cell);
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
    Position pos = cell->GetPosition();
    UpdateLabel(pos);
    SwapCellAndLabbel(pos);
    if(fgen_.IsMine(pos.x_,pos.y_)){
        qDebug() << "signam Bomb emited";
        emit signalBomb();
    }
    if(fgen_.IsFreeCell(pos.x_, pos.y_))RevealCellArea(pos);
}

void Miner::UnRevealCell(Cell* cell){
    Position pos = cell->GetPosition();
    if(cell->IsRevealed()){
         SwapCellAndLabbel(pos);
    }
}



Cell* Miner::CreateCell(Position pos){
    Cell* field = new Cell(pos.x_, pos.y_);
    connect(field, SIGNAL(ClickedP(Cell*)), SLOT(slotCellClicked(Cell*)));
    connect(field, SIGNAL(rightClicked(Cell*)), SLOT(slotCellClicked(Cell*)));//////FLAG
    field->setMaximumSize(cell_side_, cell_side_);
    return field;
}

QLabel* Miner::CreateCellLabel(){
    QLabel* lb = new QLabel();
    lb->setMaximumSize(cell_side_, cell_side_);
    lb -> setAlignment(Qt::AlignmentFlag::AlignCenter);
    return lb;
}

Cell* Miner::GetCellPtr(Position pos){
    return cells_ptrs_.at(pos.x_).at(pos.y_);
}

void Miner::RevealCellArea(Position pos){
    int x = pos.x_;
    int y  = pos. y_;
    Cell* cell = nullptr;
    bool leftValid = true;
    bool upValid = true;
    bool rightValid = true;
    bool downValid = true;
    if(x - 1 < 0) leftValid = false;
    if(y - 1 < 0) upValid = false;
    if(x + 1 > rowSize_ - 1) rightValid = false;
    if(y + 1 > columnSize_ - 1) downValid = false;
    qDebug() << "Position reveal" << x << " " << y;
    if(leftValid){
        cell = GetCellPtr(Position{x-1, y});
        if(!fgen_.IsMine(x - 1, y) && !cell->IsRevealed() ) {
            qDebug() <<"Chek "<<x-1 << " " << y<< " " <<  !fgen_.IsMine(x - 1, y) << " " << !cell->IsRevealed();
            RevealCell(cell);
        }
        if(upValid){
            cell = GetCellPtr(Position{x-1, y-1});
            if(!fgen_.IsMine(x-1, y-1) && !cell->IsRevealed()){
                qDebug()<<"Chek "<<x-1 << " " << y-1 << " "<< !fgen_.IsMine(x - 1, y-1) << " " << !cell->IsRevealed();
                RevealCell(cell);
            }
        }

    }
    if(upValid){
        cell = GetCellPtr(Position{x, y-1});
        qDebug() <<"Chek "<<x << " " << y-1<< " " <<  !fgen_.IsMine(x, y - 1 ) << " " << !cell->IsRevealed();
        if(!fgen_.IsMine(x, y-1) && !cell->IsRevealed() ){
            RevealCell(cell);
        }
        if(rightValid){
            cell = GetCellPtr(Position{x+1, y-1});
            qDebug() <<"Chek "<<x+1 << " " << y-1<< " " <<  !fgen_.IsMine(x + 1, y - 1) << " " << !cell->IsRevealed();
            if(!fgen_.IsMine(x+1, y-1) && !cell->IsRevealed() ){
                RevealCell(cell);
            }
        }
    }
    if(rightValid){
        cell = GetCellPtr(Position{x+1, y});
        qDebug() <<"Chek "<<x+1 << " " << y<< " " <<  !fgen_.IsMine(x + 1, y) << " " << !cell->IsRevealed();
        if(!fgen_.IsMine(x+1, y) && !cell->IsRevealed() ){
            RevealCell(cell);
        }
        if(downValid){
            cell = GetCellPtr(Position{x+1, y+1});
            qDebug() <<"Chek "<<x+1 << " " << y +1 << " " <<  !fgen_.IsMine(x + 1, y + 1) << " " << !cell->IsRevealed();
            if(!fgen_.IsMine(x+1, y+1) && !cell->IsRevealed() ){
                RevealCell(cell);
            }
        }
    }
    if(downValid){
        cell = GetCellPtr(Position{x, y+1});
        qDebug() <<"Chek "<<x << " " << y + 1<< " " <<  !fgen_.IsMine(x, y + 1) << " " << !cell->IsRevealed();
        if(!fgen_.IsMine(x, y+1) && !cell->IsRevealed() ){
            RevealCell(cell);
        }
        if(leftValid){
            cell = GetCellPtr(Position{x-1, y+1});
            qDebug() <<"Chek "<<x-1 << " " << y + 1<< " " <<  !fgen_.IsMine(x - 1, y + 1) << " " << !cell->IsRevealed();
            if(!fgen_.IsMine(x-1, y+1) && !cell->IsRevealed() ){
                RevealCell(cell);
            }
        }
    }
}


void Miner::SetupFieldLayout(){
    QGridLayout* qg_layout = new QGridLayout();
    qg_layout->setContentsMargins(5,5,5,5);
    qg_layout->setSpacing(0);
    for(int i = 0; i < height_ / cell_side_; ++i){
        for(int j = 0; j <  width_ / cell_side_; ++j){
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
        }
    }
    fgen_.Generate();
    fgen_.DrawField();
}

void Miner::UpdateLabel(Position pos){
    QString c(fgen_.GetCellValue(pos.x_, pos.y_));
    if (c == "0") c = " ";
    labels_ptrs_.at(pos.x_).at(pos.y_)->setText(c);
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
