#include "Grid.h"

Grid::Grid() {
    for (int x = 0; x < boardSize; ++x) {
        std::vector <Cell> p;
        std::vector <Cell> e;
        playerBoard.push_back(p);
        enemyBoard.push_back(e);
        for (int y = 0; y < 10; ++y) {
            Cell p(x, y, false, false, false);
            Cell e(x, y, false, false, true);
            playerBoard.at(x).push_back(p);
            enemyBoard.at(x).push_back(e);
        }
    }
}

void Grid::addShips() {
    for (int x = numShips + 1; x > 1; --x) {
        bool locationAllowed = true;
        Ship s (x);
        char c;
        while (true) {
            std::vector <Coordinate> doubles;
            locationAllowed = true;
            std::vector<Coordinate> coordinates = s.getCoordinates();
            for (int y = 0; y < x; ++y) {
                if (playerBoard.at(coordinates.at(y).row).at(coordinates.at(y).col).getIsShip()) {
                    locationAllowed = false;
                    break;
                }
            }
            for (int y = 0; y < x; ++y) {
                    if (playerBoard.at(coordinates.at(y).row).at(coordinates.at(y).col).getIsShip()) doubles.push_back(coordinates.at(y));
                    playerBoard.at(coordinates.at(y).row).at(coordinates.at(y).col).setIsShip(true);
            }
            std::cout << *this;
            std::cin >> c;
            if ('p'== c){ //place ship

                if (locationAllowed) {
                    playerShips.push_back(s);
                    break;
                } else {
                    std::cout << "Can't place ship here" << std::endl;
                }
            } else if (('r' == c) || ('a' == c) || ('w' == c) || ('d' == c) || ('s' == c)) {
                for (int y = 0; y < x; ++y){
                    playerBoard.at(coordinates.at(y).row).at(coordinates.at(y).col).setIsShip(false);
                    int length = doubles.size();
                    for (int d = 0; d < length; ++d) {
                            if ((doubles.at(d).col == coordinates.at(y).col) && (doubles.at(d).row == coordinates.at(y).row)) {
                                playerBoard.at(coordinates.at(y).row).at(coordinates.at(y).col).setIsShip(true);
                            }
                    }
                }
                if ('r' == c) s.rotateShip();
                else if ('a'==c) s.moveLeft();
                else if ('w'== c) s.moveUp();
                else if ('d'== c) s.moveRight();
                else s.moveDown(); //'s' == c
            }
            doubles.erase((doubles.begin(), doubles.end() - 1));
        }
    }
    //enemy ships
    for (int x = numShips + 1; x > 1; --x) {
        while (true) {
            int i, j, ns;
            i = rand() % (boardSize - x) + 1;
            j = rand() % (boardSize - x) + 1;
            ns = rand() % 2;
            Ship s (x);
            if (ns) s.rotateShip();
            for (int y = 0; y < i; ++y) s.moveDown();
            for (int y = 0; y < j; ++y) s.moveRight();
            bool locationAllowed = true;
            std::vector<Coordinate> coordinates = s.getCoordinates();
            for (int y = 0; y < x; ++y) {
                if (enemyBoard.at(coordinates.at(y).row).at(coordinates.at(y).col).getIsShip()) {
                    locationAllowed = false;
                    break;
                }
            }
            if (locationAllowed) {
                for (int y = 0; y < x; ++y) (enemyBoard.at(coordinates.at(y).row).at(coordinates.at(y).col).setIsShip(true));
                enemyShips.push_back(s);
                break;
            }
        }
    }
}

void Grid::shipDestroyed(std::vector<Ship> ships) {
    for (int x = 0; x < numShips; ++x) {
        if ((ships.at(x).totalHits == ships.at(x).length) &&
            (ships.at(x).destroyed == false)) {
                ships.at(x).destroyed = true;
                std::cout << "The ship was destroyed!" << std::endl;
            }
    }
}

void Grid::fireAt (std::vector<std::vector<Cell> >& board, std::vector<Ship>& ships, bool atEnemyBoard) {
    int c, r;
    while (true) {
        if (atEnemyBoard) {
            while (true) {
                int col;
                char row;
                char lastLetter = 'A' + boardSize - 1;
                std::cout << "Input a row from A-" << lastLetter << std::endl;
                std::cin >> row;
                std::cout << "Input a column from 1-" << boardSize << std::endl;

                std::cin >> col;
                if ((((row >= 'a') && (row <= 'j')) || ((row >= 'A') && (row <= 'J'))) &&
                    ((col >= 1) && (col <= boardSize))) {
                    c = col - 1;
                    if (row >= 'a') r = row - 'a';
                    else r = row - 'A';
                    break;
                } else {
                    std::cout << "Invalid entry" << std::endl;
                }
            }
        } else {
            r = rand() % boardSize;
            c = rand() % boardSize;
        }

        if (board.at(r).at(c).getIsHit()) {
            if (atEnemyBoard) std::cout << "You've already hit that location" << std::endl;
        }
        else break;
    }
    board.at(r).at(c).setIsHit(true);
    if (board.at(r).at(c).getIsShip()) {
        std::cout << "A ship has been hit!" << std::endl;
        for (int x = 0; x < numShips; ++x) {
            for (int y = 0; y < ships.at(x).length; ++y) {
                if ((ships.at(x).location.at(y).row == r) &&
                    (ships.at(x).location.at(y).col == c)) {
                        ++ships.at(x).totalHits;
                        break;
                    }
            }
        }
    }

}



bool Grid::noShipsLeft(std::vector<Ship> ships) const {
    for (int x = 0; x < numShips; ++x) {
        if (ships.at(x).length != ships.at(x).totalHits) return false;
    }
    return true;
}

void printOneBoard (std::ostream& out, Grid& g, bool isEnemy) {
    out << "  ";
    for (int x = 0; x < boardSize; ++x) out << x + 1 << " ";
    out << std::endl;
    for (int x = 0; x < boardSize; ++x) {
        char c = 'A' + x;
        out << c << " ";
        for (int y = 0; y < boardSize; ++y) {
            Cell c = g.getPlayerBoard().at(x).at(y);
            if (isEnemy) c = g.getEnemyBoard().at(x).at(y);
            if (c.getIsHit()) {
                if (c.getIsShip()) out << "$ ";
                else out << "x ";
            } else if ((c.getIsShip()) && !(isEnemy)) out << "S ";
            else out << ". ";
        }
        out << std::endl;
    }
    out << std::endl;
}

std::ostream &operator<<(std::ostream& out, Grid& g) {
    out << "Enemy Board" << std::endl;
    printOneBoard(out, g, true);
    for (int x = 0; x < boardSize; ++x) out << "--";

    out << std::endl << std::endl << "Player Board" << std::endl;
    printOneBoard(out, g, false);
    return out;
}


std::vector<std::vector<Cell> > Grid::getPlayerBoard() {return playerBoard;}
std::vector<std::vector<Cell> > Grid::getEnemyBoard() {return enemyBoard;}

