#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include "tile.h"
#include "loadImage.h"
#include "player.h"

using std::cout;
using std::endl;

player greg;
std::vector<tile> tiles;

void loadBoard (const string& boardName){
    string filepath = "boards/";
    filepath += boardName;
    filepath += ".brd";

    std::ifstream file(filepath);
    //read info from file if open
    if (file.is_open()){
        //vector of board pieces
        std::vector<char> boardPieces;

        //reset things in player
        greg.setWinnerStatus(false);

        while (!file.eof()){
            string line;

            for (unsigned int j = 0; j < 20; j++){
                getline(file, line);
                for (unsigned int i = 0; i < 23; i++)
                    boardPieces.push_back(line[i]);
            }
        }

//        for (unsigned int j = 0; j < 20; j++){
//            for (unsigned int i = 0; i < 23; i++){
//                cout << boardPieces[(j * 23) + i] << " ";
//            }
//            cout << endl;
//        }
//        cout << endl;

        //reset pieces of each tile based on board info
        for (unsigned int i = 0; i < tiles.size(); i++){
            if (boardPieces.at(i) == '0')
                tiles.at(i).setWalkable(false);
            if (boardPieces.at(i) == '1')
                tiles.at(i).setWalkable(true);
        }

    }
    file.close();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1449, 1480), "maze");

    //load void tiles
    for (int i = 0; i < 460; i++){
        tile tiler;
        tiler.setTileNum(i);
        tiles.push_back(tiler);
    }

    //load Textures
    loadImage::LoadTexture("stone_slab");
    loadImage::LoadTexture("lava");
    loadImage::LoadTexture("obsidian");
    loadImage::LoadTexture("easy");
    loadImage::LoadTexture("medium");
    loadImage::LoadTexture("hard");
    loadImage::LoadTexture("select_level_below");
    loadImage::LoadTexture("customize_screen");
    loadImage::LoadTexture("save_changes");
    loadImage::LoadTexture("start");
    loadImage::LoadTexture("end");
    loadImage::LoadTexture("customize_player");
    loadImage::LoadTexture("playerBig");
    loadImage::LoadTexture("player2Big");
    loadImage::LoadTexture("player");
    loadImage::LoadTexture("player2");
    loadImage::LoadTexture("heart");
    loadImage::LoadTexture("game_over");
    loadImage::LoadTexture("retry");
    loadImage::LoadTexture("quit");
    loadImage::LoadTexture("victory");
    loadImage::LoadTexture("return");

    //load Sprites
    //beginning screen
    sf::Sprite select_level_belowSprite(loadImage::GetTexture("select_level_below"));
    select_level_belowSprite.setScale(sf::Vector2f(0.75f, 0.75f));
    select_level_belowSprite.setPosition(sf::Vector2f(12.0f, 578.25f));
    //customizing screen
    sf::Sprite customize_screenSprite(loadImage::GetTexture("customize_screen"));
    customize_screenSprite.setScale(sf::Vector2f(0.9124f, 1.07f));
    sf::Sprite save_changesSprite(loadImage::GetTexture("save_changes"));
    save_changesSprite.setPosition(sf::Vector2f((724.5f - (save_changesSprite.getTexture()->getSize().x / 2.0f)), 1055.0f));
    sf::Sprite playerBigSprite(loadImage::GetTexture("playerBig"));
    playerBigSprite.setPosition(sf::Vector2f((724.5f - playerBigSprite.getTexture()->getSize().x - 15.0f), 375.0f));
    sf::Sprite player2BigSprite(loadImage::GetTexture("player2Big"));
    player2BigSprite.setPosition(sf::Vector2f((724.5f + 13.0f), 375.0f));
    //stone slabs
    std::vector<sf::Sprite> stoneSlabs;
    for (int i = 0; i < 460; i++){
        sf::Sprite stone_slabSprite(loadImage::GetTexture("stone_slab"));
        stone_slabSprite.setScale(sf::Vector2f(0.15f, 0.15f));
        stone_slabSprite.setPosition(sf::Vector2f((stone_slabSprite.getTexture()->getSize().x * stone_slabSprite.getScale().x) * (i % 23),
                (stone_slabSprite.getTexture()->getSize().y * stone_slabSprite.getScale().y) * (float)(i/23)));
        stoneSlabs.push_back(stone_slabSprite);
    }
    //lavas
    std::vector<sf::Sprite> lavas;
    for (int i = 0; i < 460; i++){
        sf::Sprite lavaSprite(loadImage::GetTexture("lava"));
        lavaSprite.setScale(sf::Vector2f(0.28f, 0.28f));
        lavaSprite.setPosition(sf::Vector2f((lavaSprite.getTexture()->getSize().x * lavaSprite.getScale().x) * (i % 23),
                                                  (lavaSprite.getTexture()->getSize().y * lavaSprite.getScale().y) * (float)(i/23)));
        lavas.push_back(lavaSprite);
    }
    //obsidians
    std::vector<sf::Sprite> obsidians;
    for (int i = 0; i < 460; i++){
        sf::Sprite obsidianSprite(loadImage::GetTexture("obsidian"));
        obsidianSprite.setScale(sf::Vector2f(0.1575f, 0.1575f));
        obsidianSprite.setPosition(sf::Vector2f((obsidianSprite.getTexture()->getSize().x * obsidianSprite.getScale().x) * (i % 23),
                                            (obsidianSprite.getTexture()->getSize().y * obsidianSprite.getScale().y) * (float)(i/23)));
        obsidians.push_back(obsidianSprite);
    }
    //start/end
    sf::Sprite startSprite(loadImage::GetTexture("start"));
    startSprite.setScale(sf::Vector2f(0.11f, 0.18f));
    startSprite.setPosition(sf::Vector2f(0.0f, 18.9f));
    sf::Sprite endSprite(loadImage::GetTexture("end"));
    endSprite.setScale(sf::Vector2f(0.17f, 0.17f));
    endSprite.setPosition(sf::Vector2f(1386.0f, 1197.0f + 18.9f));
    //level buttons
    sf::Sprite easySprite(loadImage::GetTexture("easy"));
    easySprite.setScale(sf::Vector2f(0.35f, 0.35f));
    easySprite.setPosition(20.0f, (20.0f * 63.0f) + 20.0f);
    sf::Sprite mediumSprite(loadImage::GetTexture("medium"));
    mediumSprite.setScale(sf::Vector2f(0.355f, 0.355f));
    mediumSprite.setPosition(sf::Vector2f(20.0f, (20.0f * 63.0f) + 20.0f + 48.3f + 15.0f));
    sf::Sprite hardSprite(loadImage::GetTexture("hard"));
    hardSprite.setScale(sf::Vector2f(0.355f, 0.355f));
    hardSprite.setPosition(sf::Vector2f(20.0f, (20 * 63) + 20.0f + 48.3f + 48.28f + 15.0f + 15.0f));
    //player
    sf::Sprite customize_playerSprite(loadImage::GetTexture("customize_player"));
    customize_playerSprite.setScale(sf::Vector2f(0.355f, 0.335f));
    customize_playerSprite.setPosition(sf::Vector2f(820.0f, 1400.0f));
    sf::Sprite playerSprite(loadImage::GetTexture("player"));
    playerSprite.setScale(sf::Vector2f(0.13f, 0.13f));
    sf::Sprite player2Sprite(loadImage::GetTexture("player2"));
    playerSprite.setScale(sf::Vector2f(0.13f, 0.13f));
    std::vector<sf::Sprite> hearts;
    for (unsigned int i = 0; i < 3; i++){
        sf::Sprite heartSprite(loadImage::GetTexture("heart"));
        heartSprite.setScale(sf::Vector2f(0.13f, 0.13f));
        heartSprite.setPosition(sf::Vector2f(1180.0f + ((float)i * heartSprite.getScale().x * heartSprite.getTexture()->getSize().x),
                1260.f + 40.0f));
        hearts.push_back(heartSprite);
    }
    //game status
    sf::Sprite game_overSprite(loadImage::GetTexture("game_over"));
    game_overSprite.setPosition(sf::Vector2f(724.5f - 499.0f, 630.0f - 70.0f));
    sf::Sprite retrySprite(loadImage::GetTexture("retry"));
    retrySprite.setScale(sf::Vector2f(0.65217391f, 0.65217391f));
    retrySprite.setPosition(sf::Vector2f(724.5f + 40.0f,630.0f + 70.0f + 40.0f));
    sf::Sprite quitSprite(loadImage::GetTexture("quit"));
    quitSprite.setScale(sf::Vector2f(0.6f, 0.6f));
    quitSprite.setPosition(sf::Vector2f(724.5f - 40.0f - (quitSprite.getTexture()->getSize().x * quitSprite.getScale().x),
            630.0f + 70.0f + 40.0f));
    sf::Sprite victorySprite(loadImage::GetTexture("victory"));
    victorySprite.setPosition(sf::Vector2f(724.5f - 360.0f,630.0f - 70.0f));
    sf::Sprite returnSprite (loadImage::GetTexture("return"));
    returnSprite.setScale(sf::Vector2f(0.8f, 0.8f));
    returnSprite.setPosition(sf::Vector2f(724.5f - ((returnSprite.getTexture()->getSize().x * returnSprite.getScale().x) / 2.0f),
            740.0f));


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            //during gameplay
            if (!greg.getLoserStatus() && !greg.getWinnerStatus()){
                if (event.type == sf::Event::MouseButtonPressed){

                    if (event.mouseButton.button == sf::Mouse::Left){
                        //get position
                        auto mousePosition = sf::Mouse::getPosition(window);

                        //customization stuff
                        if (customize_playerSprite.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y)))
                            greg.setCustomizing(true);
                        if (save_changesSprite.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y)))
                            greg.setCustomizing(false);

                        //click level button
                        if (easySprite.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y))){
                            greg.levelChosen = "easy";
                            loadBoard("easy");
                            greg.setBlockNum("reset");
                            greg.resetLives();
                            playerSprite.setPosition(sf::Vector2f(0.0f, 0.0f));

                        }
                        if (mediumSprite.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y))){
                            greg.levelChosen = "medium";
                            loadBoard("medium");
                            greg.setBlockNum("reset");
                            greg.resetLives();
                            playerSprite.setPosition(sf::Vector2f(0.0f, 0.0f));
                        }
                        if (hardSprite.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y))){
                            greg.levelChosen = "hard";
                            loadBoard("hard");
                            greg.setBlockNum("reset");
                            greg.resetLives();
                            playerSprite.setPosition(sf::Vector2f(0.0f, 0.0f));
                        }
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && greg.levelChosen != "none"){
                    if (playerSprite.getPosition().x >= 63.0f){
                        greg.setBlockNum("left");
                        playerSprite.setPosition(sf::Vector2f(playerSprite.getPosition().x - 63.0f, playerSprite.getPosition().y));
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && greg.levelChosen != "none"){
                    if (playerSprite.getPosition().x <= 1323.0f){
                        greg.setBlockNum("right");
                        playerSprite.setPosition(sf::Vector2f(playerSprite.getPosition().x + 63.0f, playerSprite.getPosition().y));
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && greg.levelChosen != "none"){
                    if (playerSprite.getPosition().y >= 63.0f){
                        greg.setBlockNum("up");
                        playerSprite.setPosition(sf::Vector2f(playerSprite.getPosition().x, playerSprite.getPosition().y - 63.0f));
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && greg.levelChosen != "none"){
                    if (playerSprite.getPosition().y <= 1134.0f){
                        greg.setBlockNum("down");
                        playerSprite.setPosition(sf::Vector2f(playerSprite.getPosition().x, playerSprite.getPosition().y + 63.0f));
                    }
                }
            }

            //losing screen
            if (greg.getLoserStatus() && event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left){
                    //get position
                    auto mousePosition = sf::Mouse::getPosition(window);

                    //click retry
                    if (retrySprite.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y))){
                        greg.setBlockNum("reset");
                        greg.resetLives();
                        greg.setLoserStatus(false);
                        playerSprite.setPosition(sf::Vector2f(0.0f, 0.0f));
                    }

                    //click quit
                    if (quitSprite.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y))){
                        window.close();
                    }
                }
            }

            //victory screen
            if (greg.getWinnerStatus() && event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left){
                    //get position
                    auto mousePosition = sf::Mouse::getPosition(window);

                    //click return
                    if (returnSprite.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y))){
                        greg.setBlockNum("reset");
                        greg.resetLives();
                        greg.setWinnerStatus(false);
                        playerSprite.setPosition(sf::Vector2f(0.0f, 0.0f));
                        greg.levelChosen = "none";
                    }
                }
            }
        }//end of events

        //reset greg if needed
        for (unsigned int i = 0; i < tiles.size(); i++){
            if (!tiles.at(i).getWalkable() && (i == greg.getBlockNum()) && (greg.levelChosen != "none")){
                greg.removeLife();
                if (greg.getLivesLeft() >= 0){
                    greg.setBlockNum("reset");
                    playerSprite.setPosition(sf::Vector2f(0.0f, 0.0f));
                }
            }
        }

        //if greg makes it to end (aka victory)
        if (greg.getBlockNum() == 459){
            greg.setWinnerStatus(true);
        }

        //only do once
        window.clear();

        //draw before screen
        if (greg.levelChosen == "none"){
            window.draw(select_level_belowSprite);
        }
        window.draw(customize_playerSprite);

        //draw level buttons
        window.draw(easySprite);
        window.draw(mediumSprite);
        window.draw(hardSprite);

        //draw board
        if (greg.levelChosen != "none"){
            //draw floor
            for (unsigned int i = 0; i < tiles.size(); i++){
                if (tiles.at(i).getWalkable())
                    window.draw(stoneSlabs.at(i));
                else if (!tiles.at(i).getWalkable())
                    window.draw(lavas.at(i));
            }

            //draw start/end
            window.draw(startSprite);
            window.draw(endSprite);

            //draw player
            window.draw(playerSprite);

            //draw black out except for around me
            if (!greg.getWinnerStatus() && !greg.getLoserStatus()){
                for (unsigned int i = 0; i < obsidians.size(); i++){
                    if (i != greg.getBlockNum()){
                        //top right corner
                        if (greg.getBlockNum() == 0){
                            if (i != 1 && i != 24 && i != 23)
                                window.draw(obsidians.at(i));
                        }
                            //top left corner
                        else if (greg.getBlockNum() == 22){
                            if (i != 21 && i != 44 && i != 45)
                                window.draw(obsidians.at(i));
                        }
                            //bottom left corner
                        else if (greg.getBlockNum() == 437){
                            if (i!= 414 && i != 415 & i != 438)
                                window.draw(obsidians.at(i));
                        }
                            //bottom right corner
                        else if (greg.getBlockNum() == 459){
                            if (i != 458 && i != 435 && i != 436)
                                window.draw(obsidians.at(i));
                        }
                            //top edge
                        else if ((greg.getBlockNum() / 23) == 0){
                            if (i != (greg.getBlockNum() - 1) && i != (greg.getBlockNum() + 1) && i != (greg.getBlockNum() + 23) &&
                                i != (greg.getBlockNum() - 1 + 23) && i != (greg.getBlockNum() + 1 + 23))
                                window.draw(obsidians.at(i));
                        }
                            //bottom edge
                        else if ((greg.getBlockNum() / 23) == 19){
                            if (i != (greg.getBlockNum() - 1) && i != (greg.getBlockNum() + 1) && i != (greg.getBlockNum() - 23) &&
                                i != (greg.getBlockNum() - 1- 23) && i != (greg.getBlockNum() + 1 - 23))
                                window.draw(obsidians.at(i));
                        }
                            //left edge
                        else if ((greg.getBlockNum() % 23) == 0){
                            if (i != (greg.getBlockNum() - 23) && i != (greg.getBlockNum() - 23 + 1) && i != (greg.getBlockNum() + 1) &&
                                i != (greg.getBlockNum() + 23 + 1) && i != (greg.getBlockNum() + 23))
                                window.draw(obsidians.at(i));
                        }
                            //right edge
                        else if ((greg.getBlockNum() % 23) == 22){
                            if (i != (greg.getBlockNum() - 23) && i != (greg.getBlockNum() - 23 - 1) && i != (greg.getBlockNum() - 1) &&
                                i != (greg.getBlockNum() + 23 -1) && i != (greg.getBlockNum() + 23))
                                window.draw(obsidians.at(i));
                        }
                            //anywhere else
                        else{
                            if (i != (greg.getBlockNum() - 23) && i != (greg.getBlockNum() - 23 + 1) && i != (greg.getBlockNum() + 1) &&
                                i != (greg.getBlockNum() + 23 + 1) && i != (greg.getBlockNum() + 23) && i != (greg.getBlockNum() + 23 - 1) &&
                                i != (greg.getBlockNum() - 1) && i != (greg.getBlockNum() - 23 - 1))
                                window.draw(obsidians.at(i));
                        }
                    }
                }
            }

            //draw with lives
            if (greg.getLivesLeft() >= 0){
                for (unsigned int i = 0; i < greg.getLivesLeft(); i++){
                    window.draw(hearts.at(i));
                }
            }
            else if (greg.getLivesLeft() < 0)
                greg.setLoserStatus(true);
        }

        //custom screen
        if (greg.getCustomizing()){
            window.draw(customize_screenSprite);
            window.draw(playerBigSprite);
            window.draw(player2BigSprite);
            window.draw(save_changesSprite);
        }

        //draw losing screen
        if (greg.getLoserStatus()){
            window.draw(game_overSprite);
            window.draw(retrySprite);
            window.draw(quitSprite);
        }

        //draw winning screen
        if (greg.getWinnerStatus()){
            window.draw(victorySprite);
            window.draw(returnSprite);
        }

        //only do once
        window.display();
    }
    return 0;
}