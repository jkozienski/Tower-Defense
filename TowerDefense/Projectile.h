#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "TextureManager.h"
#include "Player.h"
#include <iostream>

class Projectile {
private:
    Player* player;
    TextureManager* textureManager;
    sf::Sprite sprite;
    sf::Vector2f velocity;
    float speed;
    bool active;
    sf::Vector2f position;
    sf::Vector2f direction;

public:
    // Konstruktor
    Projectile(Player* player, TextureManager*, sf::Vector2f startPosition, sf::Vector2f direction, float speed);
    bool isActive() const;
    void const changeActive(bool state);
    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getPosition() const;
    void update(const float& dt);
    void render(sf::RenderTarget* target);


};

