#include "Projectile.h"


Projectile::Projectile(Player* player, TextureManager* textureManager, sf::Vector2f startPosition, sf::Vector2f direction, float speed)
    : position(startPosition), direction(direction), speed(speed), active(true)
{
    this->sprite.setTexture(this->textureManager->getTexture("Projectile1"));

    this->sprite.setPosition(startPosition);

}

bool Projectile::isActive() const {
    return active;
}

void const Projectile::changeActive(bool state)
{
    this->active = state;
}

sf::FloatRect Projectile::getGlobalBounds() const
{
    return this->sprite.getGlobalBounds();
}


sf::Vector2f Projectile::getPosition() const {
    return position;
}

void Projectile::update(const float& dt) {
    if (active) {
        position += direction * speed * dt;
        sprite.setPosition(position);
    }
}

void Projectile::render(sf::RenderTarget* target) {
    if (active) {
        target->draw(sprite);
    }
}