#include <iostream>
#include "Grid.h"
#include "Size.h"
using namespace std;

int boardSize;
int numShips;
int level;

int main () {
    srand (time(NULL));
    std::cout << "Welcome to battleship" << std::endl << "Choose Level";
    boardSize = 10;
    numShips = 6;
    Grid g;
    g.addShips();
    std::cout << g;
    while (true) {

        g.fireAt(g.enemyBoard, g.enemyShips, true);
        std::cout << g;
        g.shipDestroyed(g.enemyShips);

        if (g.noShipsLeft(g.enemyShips)) { //win
            std::cout << "You Win!" << std::endl;
            break;
        }

        //enemy fires
        g.fireAt(g.playerBoard, g.playerShips, false);
        std::cout << g;
        g.shipDestroyed(g.playerShips);
        if (g.noShipsLeft(g.playerShips)) { //loss
            std::cout << "You Lose!" << std::endl;
            break;
        }

    }
}
