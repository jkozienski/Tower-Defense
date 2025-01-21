#include "Map.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>



Map::Map(const std::string& filename, float widthTile, float heightTile, TextureManager* textureManager) : widthTile(widthTile), heightTile(heightTile), textureManager(textureManager){
    this->sprite.setTexture(this->textureManager->getTexture("PathTile"));
    std::ifstream mapFile(filename);
    if (mapFile.is_open()) {
        std::string line;

        while (std::getline(mapFile, line)) {
            std::vector<char> row;
            std::vector<sf::RectangleShape> rowRects;

            for (char symbol : line) {
                row.push_back(symbol);

                sf::RectangleShape rect(sf::Vector2f(widthTile, heightTile)); // Rozmiar pola (mo¿esz dostosowaæ)
                rect.setFillColor(sf::Color::Transparent); // Ustawiamy kolor wype³nienia na przezroczysty
                rect.setOutlineThickness(0.1f); // Gruboœæ obrysu
                rect.setOutlineColor(sf::Color::Black); // Kolor obrysu

                rowRects.push_back(rect);
            }

            grid.push_back(row);
            rects.push_back(rowRects);
           
        }

        mapFile.close();
        this->pathDistance = 0;
    }
    else {
        std::cerr << "Nie mozna otworzyc pliku "<< filename << std::endl;
    }
}



sf::Vector2i Map::getSize() const {
    return sf::Vector2i(grid[0].size(), grid.size());
}

char Map::getTile(float x, float y) const {
    return grid[y][x]; //'y' indeks wiersza, 'x' indeks kolumny
}

const float& Map::getWidthTile() const
{
    return this->widthTile;
}

const float& Map::getHeightTile() const
{
    return this->heightTile;
}

const float& Map::getHeightMap() const
{
    return this->heightTile*15;//szerokoœæ pola razy ilosc pól by³ ?40 bo 20pol?
}
const float& Map::getWidthMap() const
{
    return this->widthTile*28;
}

const bool& Map::getIsTileFree() const
{
    return this->isTileFree;
}

sf::Vector2f Map::getEndTilePosition() const
{
   for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] == 'E') {
                return sf::Vector2f(x * this->widthTile, y * this->heightTile);
            }
        }
    }
    return sf::Vector2f(-1, -1); // zwraca nieprawid³ow¹ pozycje, jeœli nie znaleziono 'E'

}

const sf::Vector2f& Map::getPathTile() const
{
    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] == 'T') {
                return sf::Vector2f(x * this->widthTile, y * this->heightTile);
            }
        }
    }
    return sf::Vector2f(-1, -1); // zwraca nieprawid³ow¹ pozycje, jesli nie znalezniono

}
void Map::setWidthTile(float width)
{
    this->widthTile = width;

}
void Map::setHeightTile(float height)
{
    this->heightTile = height;

}


const int& Map::getPathDistance() const {
    return this->pathDistance;
}

bool Map::canPlaceTower(float x, float y) const {
    if (x < 0 || y < 0 || x >= this->getWidthMap() || y >= this->getHeightMap()) {
            return false;  // Sprawdza czy pozycja jest w granicach mapy
    }

    char tile = this->getTile(x, y);
    
    return tile == '.';  // Tylko na polach '.' mo¿na postawiæ wieze
}

const std::vector<std::vector<char>>& Map::getGrid() const {
    return grid;
}


sf::Vector2f Map::getTilePosition(float x, float y) const
{
    return sf::Vector2f(x * this->widthTile + this->widthTile / 2.0f, y * this->heightTile + this->heightTile / 2.0f);
}

void Map::update(const float& dt)
{
}

void Map::render(sf::RenderWindow* target) {

    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid[y].size(); ++x) {

            // Ustawiamy kolor dla pól
            if (grid[y][x] == 'T') {
                this->isTileFree = false;
                sf::Color tileColor = sf::Color::Magenta;
                tileColor.a = 64;
                rects[y][x].setFillColor(tileColor);
                
                if (x * this->widthTile < 1248) {
                    sprite.setPosition(x * this->widthTile, y * this->heightTile);
                    target->draw(sprite);
                }
                //target->draw(rects[y][x]);
                this->pathDistance++;

            }
            else if (grid[y][x] == 'E') {
                this->isTileFree = false;
                sf::Color tileColor = sf::Color::Red;
                tileColor.a = 64;
                rects[y][x].setFillColor(tileColor);
            }
            else if (grid[y][x] == 'S') {
                this->isTileFree = false;
                sf::Color tileColor = sf::Color::Blue;
                tileColor.a = 64;
                rects[y][x].setFillColor(tileColor);
            }
            else if (grid[y][x] == 'X') {
                this->isTileFree = false;
                sf::Color tileColor = sf::Color::Green;
                tileColor.a = 64;
                rects[y][x].setFillColor(tileColor);
            }
            else {
                this->isTileFree = true;
                sf::Color tileColor = sf::Color::White;
                tileColor.a = 32;
                //rects[y][x].setFillColor(tileColor);
                target->draw(rects[y][x]);
                
            }
           
        }
    }

}