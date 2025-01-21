#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#include "Projectile.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "WaveManager.h";

#include <iostream>
#include <string>
#include <cmath>
#include <thread>

class Tower
{
protected:
    sf::CircleShape shape;
    sf::CircleShape rangeCoverage;
    sf::Vector2f position;
       
    sf::Vector2i TEMPmousePos;
    sf::Vector2f mousePos;
    Player* player;
    WaveManager* waveManager;
    TextureManager* textureManager;
    SoundManager* soundManager;
    int damage;
    int range;
    int cost;
    bool showRange = false;
    Enemy* targetEnemy;
    std::vector<Enemy*> killedEnemies;

    sf::Texture projectilePrototype;
    std::vector<Projectile*> projectiles;
    float projectileSpeed;

    bool projectileActive;
    Projectile* activeProjectile;
    bool projectileHit;
 


public:

    // Konstruktor
    Tower( float projectileSpeed, TextureManager* textureManager, SoundManager* soundManager, WaveManager* waveManager,Player* player, int towerDamage, int towerRange, int towerCost);
    ~Tower();

    sf::Sprite sprite;
    bool isActive = false;
    std::vector<Enemy*> getKilledEnemies();
    // Wirtualna metoda do wyœwietlania informacji o wie¿y
    virtual void displayInfo() const = 0;
    virtual void updateMousePos(sf::RenderWindow* window) = 0;
    void setPosition(float x, float y);
    sf::Vector2f& getPosition();
    void toggleRangeVisibility();
    void handleMouseInteraction(const sf::Vector2f& mousePos);
    
    void checkCollisions();
    void detectEnemies();
    void fire();
    void updateProjectiles(const float& dt);
    Enemy* getEnemy();
    sf::Clock fireClock;
    sf::Time fireInterval;

    int getTowerCost();
    void update(const float& dt);
    void render(sf::RenderTarget* target);

};

