//
// Created by Nicole Telesz on 5/4/20.
//

#include "player.h"

void player::setCustomizing(bool status) {
    customizing = status;
}

bool player::getCustomizing() {
    return customizing;
}

void player::setCharChosen(bool status) {
    charChosen = status;
}

bool player::getCharChosen() {
    return charChosen;
}

void player::setPlayer(sf::Sprite sprite) {
    playerSprite = sprite;
}

sf::Sprite player::getPlayer() {
    return playerSprite;
}

void player::setName(std::string name) {
    playerName = name;
}

std::string player::getName() {
    return playerName;
}

void player::setWinnerStatus(bool status) {
    winner = status;
}

bool player::getWinnerStatus() {
    return winner;
}

void player::setLoserStatus(bool status) {
    loser = status;
}

bool player::getLoserStatus() {
    return loser;
}

void player::setBlockNum(std::string direction) {
    if (direction == "right")
        blocknum += 1;
    else if (direction == "left")
        blocknum -= 1;
    else if (direction == "up")
        blocknum -= 23;
    else if (direction == "down")
        blocknum += 23;
    else if (direction == "reset")
        blocknum = 0;
}

int player::getBlockNum() {
    return blocknum;
}

void player::removeLife() {
    numLivesLeft -= 1;
}

void player::resetLives() {
    numLivesLeft = 3;
}

int player::getLivesLeft() {
    return numLivesLeft;
}