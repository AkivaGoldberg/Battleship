#ifndef SHIP_H
#define SHIP_H
#include <vector>
#include "Coordinate.h"
#include "Size.h"

class Ship {
    int length;
    int totalHits;
    bool destroyed;
    std::vector<Coordinate> location;
    bool NS; //orientation
  public:
    Ship(int length);
    std::vector<Coordinate> getCoordinates();
    void rotateShip();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    friend class Grid; //probably controlla
};

#endif // SHIP_H
