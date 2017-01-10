#include "Ship.h"
Ship::Ship(int length) : length{length}, totalHits{0}, NS{true} {
    destroyed = false;
    for (int x = 0; x < length; ++x) {
        Coordinate c = {x, 0};
        location.push_back(c);
    }
}

std::vector<Coordinate> Ship::getCoordinates() {return location;}

void Ship::rotateShip() {
    location.erase(location.begin(), location.end());
    if (NS) {
        for (int x = 0; x < length; ++x) {
            Coordinate c = {0, x};
            location.push_back(c);
        }
    } else {
        for (int x = 0; x < length; ++x) {
            Coordinate c = {x, 0};
            location.push_back(c);
        }
    }
}

void Ship::moveRight() {
    if (location.at(length-1).col < boardSize-1) {
        for (int x = 0; x < length; ++x) ++location.at(x).col;
    }
}

void Ship::moveLeft() {
    if (location.at(0).col > 0) {
        for (int x = 0; x < length; ++x) --location.at(x).col;
    }
}

void Ship::moveUp() {
    if (location.at(0).row > 0) {
        for (int x = 0; x < length; ++x) --location.at(x).row;
    }
}

void Ship::moveDown() {
    if (location.at(length-1).row < boardSize-1) {
        for (int x = 0; x < length; ++x) ++location.at(x).row;
    }
}
