//
// Created by Nicole Telesz on 5/4/20.
//

#pragma once


class tile{
private:
    int tilenum;
    bool walkable;

public:
    void setTileNum(int num);
    int getTileNum();

    void setWalkable(bool status);
    bool getWalkable();

};