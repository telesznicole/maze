//
// Created by Nicole Telesz on 5/4/20.
//

#include "loadImage.h"


unordered_map<string, sf::Texture> loadImage::textures;

void loadImage::LoadTexture(const char* filename){
    string filepath = "images/";
    filepath += filename;
    filepath += ".png";

    textures[filename].loadFromFile(filepath);
}

sf::Texture& loadImage::GetTexture(const  char* textureKey){
    return textures[textureKey];
}