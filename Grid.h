#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "Cell.h"
#include "Ship.h"


class Grid
{
        public:

        std::vector<std::vector<Cell> > playerBoard;
        std::vector<std::vector<Cell> > enemyBoard;
        std::vector<Ship> playerShips;
        std::vector<Ship> enemyShips;
        void shipDestroyed(std::vector<Ship> ships);
        void fireAt (std::vector<std::vector<Cell> >& board, std::vector<Ship>& ships, bool atEnemyBoard);
        bool noShipsLeft(std::vector<Ship> ships) const;

        Grid();
        void makeBoard();
        void addShips();
        std::vector<std::vector<Cell> > getPlayerBoard();
        std::vector<std::vector<Cell> > getEnemyBoard();

        friend std::ostream &operator<<(std::ostream& out, Grid& g);

};

#endif // GRID_H
