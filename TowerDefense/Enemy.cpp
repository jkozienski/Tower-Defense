#include "Enemy.h"

Enemy::Enemy(const sf::Vector2f& startPos, int health, int maxHealth, int damage, float speed, int coins, int score ,Map* map, TextureManager* textureManager, Player* player)
    : position(startPos), health(health), maxHealth(health), damage(damage), speed(speed), coins(coins), score(score), map(map), textureManager(textureManager),player(player)
{
    
    this->isAlive = true;
    this->isFinished = false;

    //this->healthBar.setSize(sf::Vector2f(46.f, 8.f));
    //this->healthBar.setFillColor(sf::Color::Red);

}

Enemy::~Enemy()
{
}

//po³owa szerokosci pola 48/2=24
const sf::Vector2f& Enemy::getPosition() const { return sf::Vector2f(position.x, position.y ); }
int Enemy::getHealth() const { return health; }
int Enemy::getDamage() const { return damage; }
float Enemy::getSpeed() const { return speed; }

int Enemy::getCoins() const
{
    return this->coins;
}

int Enemy::getScore() const
{
    return this->score;
}

const bool& Enemy::getAlive() const
{
    return this->isAlive;
}

const bool& Enemy::getFinished() const
{
    return this->isFinished;
}

const sf::RectangleShape& Enemy::getShape() const
{
    return this->shape;
}

void Enemy::setPosition(sf::Vector2f& newPosition)
{
    this->shape.setPosition(this->position.x = newPosition.x, this->position.y = newPosition.y);
    this->sprite.setPosition(this->position.x = newPosition.x, this->position.y = newPosition.y);
    //this->healthBar.setPosition(this->position.x = newPosition.x+1.f, this->position.y = newPosition.y);


}

void Enemy::setHealth(int newHealth){this->health = newHealth;}

void Enemy::decreaseHealth(int amount)
{
   this->health -= amount;
    if (health < 0) {
        health = 0;
    }
}
void Enemy::setDamage(int newDamage){this->damage = newDamage;}
void Enemy::setSpeed(float newSpeed){this->speed = newSpeed;}

void Enemy::setAlive(bool newAlive)
{
    this->isAlive = newAlive;
    
}

void Enemy::toggleHealthVisibility()
{
    this->showHP = !showHP; 
}

void Enemy::handleMouseInteraction(const sf::Vector2f& mousePos)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

        if (this->sprite.getGlobalBounds().contains(mousePos)) {
            this->toggleHealthVisibility();
        }
    }
}

sf::FloatRect Enemy::getGlobalBounds() const
{
    return this->sprite.getGlobalBounds();
}


void Enemy::moveToNextTile(const Map* map, const float& dt) {
    // Pobieramy aktualn¹ pozycjê przeciwnika
    float currPosX = round(this->getPosition().x);
    float currPosY = round(this->getPosition().y);
  
    sf::Vector2f currentPosition = sf::Vector2f(currPosX, currPosY);
   //std::cout << currentPosition.x << " " << currentPosition.y << " currentPosition\n";

    this->movementSpeed = speed*dt*1000.f;

    sf::Vector2f nextPositionRight = currentPosition + sf::Vector2f(map->getWidthTile(), 0.f);

    if (nextPositionRight.x <= 0 || map->getTile(nextPositionRight.x / map->getWidthTile(), nextPositionRight.y / map->getHeightTile()) == 'X') {
        this->shape.setPosition(this->position.x += this->movementSpeed, this->position.y);
        this->sprite.setPosition(this->position.x += this->movementSpeed, this->position.y);

        //std::cout << currentPosition.x << " " << currentPosition.y << " currentPosition\n";
       
    }
    else {

        // Sprawdzamy kierunek prawo
        if (1) {
            if (nextPositionRight.x >= 0 && nextPositionRight.x < map->getWidthMap() &&
                nextPositionRight.y >= 0 && nextPositionRight.y < map->getHeightMap() &&
                map->getTile(nextPositionRight.x / map->getWidthTile(), nextPositionRight.y / map->getHeightTile()) == 'T') {
                //std::cout << "Tile prawo:\n";

                this->shape.setPosition(this->position.x += this->movementSpeed, this->position.y);
                this->sprite.setPosition(this->position.x += this->movementSpeed, this->position.y);
                //this->healthBar.setPosition(this->position.x, this->position.y+48.f);


                movedRight = true;
                movedUp = false;
                movedDown = false;

                return;
            }
        }

        // Sprawdzamy kierunek dó³
        sf::Vector2f nextPositionDown = currentPosition + sf::Vector2f(0.f, map->getHeightTile());
        if (!movedUp) {
            if (nextPositionDown.x >= 0 && nextPositionDown.x < map->getWidthMap() &&
                nextPositionDown.y >= 0 && nextPositionDown.y < map->getHeightMap() &&
                map->getTile(nextPositionDown.x / map->getWidthTile(), nextPositionDown.y / map->getHeightTile()) == 'T') {
                // std::cout << "Tile dol:\n";

                this->shape.setPosition(this->position.x, this->position.y += this->movementSpeed);
                this->sprite.setPosition(this->position.x, this->position.y += this->movementSpeed);
                //is->healthBar.setPosition(this->position.x, this->position.y +48.f);

                movedRight = false;
                movedUp = false;
                movedDown = true;
                return;
            }
        }

        // Sprawdzamy kierunek góra
        sf::Vector2f nextPositionUp = currentPosition - sf::Vector2f(0.f, map->getHeightTile());
        if (!movedDown) {
            if (nextPositionUp.x >= 0 && nextPositionUp.x < map->getWidthMap() &&
                nextPositionUp.y >= 0 && nextPositionUp.y < map->getHeightMap() &&
                map->getTile(nextPositionUp.x / map->getWidthTile(), nextPositionUp.y / map->getHeightTile()) == 'T') {

                // std::cout << "Tile gora:\n";
                this->shape.setPosition(this->position.x, this->position.y -= this->movementSpeed);
                this->sprite.setPosition(this->position.x, this->position.y -= this->movementSpeed);
                //is->healthBar.setPosition(this->position.x, this->position.y + 48.f);

                movedUp = true;
                movedRight = false;
                movedDown = false;
                return;
            }
        }

        // Sprawdzamy czy przeciwnik doszed³ do mety
        if (map->getTile(nextPositionRight.x / map->getWidthTile(), nextPositionRight.y / map->getHeightTile()) == 'E') {
            this->setPosition(nextPositionRight);
                this->isFinished = true;
                
                this->player->decreaseHealth(1);
                this->setAlive(false);
        }
    }
      
 
    return;

    
}

