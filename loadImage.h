//
// Created by Nicole Telesz on 5/4/20.
//

#pragma once

#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <string>

using std::string;
using std::unordered_map;


class loadImage{
private:
    static unordered_map<string, sf::Texture> textures;
public:
    static void LoadTexture(const char* filename);
    static sf::Texture& GetTexture(const char* textureKey);
};