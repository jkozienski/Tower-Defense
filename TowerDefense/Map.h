#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <iostream>


#include <SFML/Graphics.hpp>
#include "TextureManager.h"


class Map {
protected:

    std::vector<std::vector<sf::RectangleShape>> rects; // Przechowuje prostok¹tne kszta³ty
    std::vector<std::vector<char>> grid; // Przechowuje uk³ad mapy
    TextureManager* textureManager;
    sf::Sprite sprite;
    int pathDistance;
    float widthTile;
    float heightTile;
    bool isTileFree;

public:

    Map(const std::string& filename, float widthTile, float heightTile, TextureManager* textureManager);

   
    sf::Vector2i getSize() const; // Metoda zwracaj¹ca rozmiar mapy
    char getTile(float x, float y) const;

    const float& getWidthTile() const;
    const float& getHeightTile() const;
    const float& getHeightMap() const;
    const float& getWidthMap() const;
    const bool& getIsTileFree() const;
    const int& getPathDistance() const;

    sf::Vector2f getEndTilePosition() const;
    const sf::Vector2f& getPathTile() const;

    void setWidthTile(float width);
    void setHeightTile(float height);

    bool canPlaceTower(float x, float y) const;


    const std::vector<std::vector<char>>& getGrid() const;
    sf::Vector2f getTilePosition(float x, float y) const;

    void update(const float& dt);
    void render(sf::RenderWindow* target);
};