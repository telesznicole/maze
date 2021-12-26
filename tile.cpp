//
// Created by Nicole Telesz on 5/4/20.
//
#include "tile.h"

void tile::setTileNum(int num) {
    tilenum = num;
}

int tile::getTileNum() {
    return tilenum;
}

void tile::setWalkable(bool status) {
    walkable = status;
}

bool tile::getWalkable() {
    return walkable;
}