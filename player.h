//
// Created by Nicole Telesz on 5/4/20.
//

#pragma once

#include <string>
#include <SFML/Graphics/Sprite.hpp>

class player{
private:
    bool customizing = false;
    bool charChosen = false;
    sf::Sprite playerSprite;
    std::string playerName = "greg";
    bool winner = false;
    bool loser = false;
    int blocknum = 0;
    int numLivesLeft = 3;
public:
    void setCustomizing(bool status);
    bool getCustomizing();
    void setCharChosen(bool status);
    bool getCharChosen();
    void setPlayer(sf::Sprite);
    sf::Sprite getPlayer();
    void setName(std::string name);
    std::string getName();
    void setWinnerStatus(bool status);
    bool getWinnerStatus();
    void setLoserStatus(bool status);
    bool getLoserStatus();
    void setBlockNum(std::string direction);
    int getBlockNum();
    void removeLife();
    void resetLives();
    int getLivesLeft();

    std::string levelChosen = "none";
};