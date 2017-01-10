#ifndef CELL_H
#define CELL_H
#include <string>

class Cell
{
    int row;
    int col;
    bool isHit;
    bool isShip;
    bool isOnEnemyBoard;
    public:
        Cell(int row, int col, bool isHit,bool isShip, bool isOnEnemyBoard);
        bool getIsHit();
        void setIsHit(bool b);
        bool getIsShip();
        void setIsShip(bool b);
        bool getIsOnEnemyBoard ();
        int getRow();
        int getCol();

};

#endif // CELL_H
