#include "Position.h"

Position::Position(int x, int y) : x_(x), y_(y)
{

}

bool isValidPosition(Position pos){
    bool valid = true;
    if(pos.x_ < 0 || pos.y_ < 0 || pos.x_ > 16-1 || pos.y_ > 16-1){
        valid = false;
    }
    return valid;

}

std::list<Position> GetPositionArea(Position pos){
    std::list<Position> PositionsArea;
    PositionsArea.push_back(Position(pos.x_-1,pos.y_-1));
    PositionsArea.push_back(Position(pos.x_-1,pos.y_));
    PositionsArea.push_back(Position(pos.x_-1,pos.y_+1));
    PositionsArea.push_back(Position(pos.x_,pos.y_-1));
    PositionsArea.push_back(Position(pos.x_,pos.y_+1));
    PositionsArea.push_back(Position(pos.x_+1,pos.y_-1));
    PositionsArea.push_back(Position(pos.x_+1,pos.y_));
    PositionsArea.push_back(Position(pos.x_+1,pos.y_+1));
    PositionsArea.remove_if([](Position pos){
        return !isValidPosition(pos);
    });
    return PositionsArea;
}
