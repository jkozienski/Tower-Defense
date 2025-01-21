#include "EnemyMedium.h"

EnemyMedium::EnemyMedium(const sf::Vector2f& startPos, int health, int maxHealth, int damage, float speed, int coins, int score, Map* map, TextureManager* textureManager, Player* player)
    : Enemy(startPos, health, maxHealth, damage, speed, coins, score, map,textureManager,player)
{
    this->shape.setSize(sf::Vector2f(47.f, 47.f));

    this->shape.setPosition(startPos);
    this->shape.setFillColor(sf::Color::Yellow);
    this->sprite.setTexture(this->textureManager->getTexture("TankMedium"));

}


void EnemyMedium::update(const float& dt) {
        this->moveToNextTile(this->map, dt);
}


void EnemyMedium::render(sf::RenderTarget* target) {

    target->draw(this->sprite);
   /* if (this->showHP) {
        target->draw(this->healthBar);
    }*/
}



