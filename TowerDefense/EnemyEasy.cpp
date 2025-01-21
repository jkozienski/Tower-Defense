#include "EnemyEasy.h"

EnemyEasy::EnemyEasy(const sf::Vector2f& startPos, int health, int maxHealth, int damage, float speed, int coins, int score, Map* map, TextureManager* textureManager, Player* player)
    : Enemy(startPos, health, maxHealth, damage, speed, coins, score, map,textureManager,player) 
{
    this->shape.setSize(sf::Vector2f(47.f, 47.f));
    this->shape.setPosition(startPos);
    this->shape.setFillColor(sf::Color::Green);
    this->sprite.setTexture(this->textureManager->getTexture("TankEasy"));
}


void EnemyEasy::update(const float& dt) {
    this->moveToNextTile(this->map, dt);
}

void EnemyEasy::render(sf::RenderTarget* target) {

    target->draw(this->sprite);
   /* if (this->showHP) {
        target->draw(this->healthBar);
    }*/
}



