#include "Cell.h"

Cell::Cell (int row, int col, bool isHit, bool isShip, bool isOnEnemyBoard) :
    row{row}, col{col}, isHit{isHit}, isShip{isShip}, isOnEnemyBoard{isOnEnemyBoard}{}
bool Cell::getIsHit() {return isHit;}
bool Cell::getIsShip() {return isShip;}
int Cell::getRow() {return row;}
int Cell::getCol() {return col;}

void Cell::setIsHit(bool b) {isHit = b;}
void Cell::setIsShip(bool b) {isShip = b;}
