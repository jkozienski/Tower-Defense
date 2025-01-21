#include "Tower.h"

Tower::Tower( float projectileSpeed, TextureManager* textureManager, SoundManager* soundManager, WaveManager* waveManager,Player* player, int towerDamage, int towerRange, int towerCost)
    :  projectileSpeed(projectileSpeed), textureManager(textureManager), soundManager(soundManager), player(player), waveManager(waveManager), damage(towerDamage), range(towerRange), cost(towerCost) {
    this->showRange = false;
    this->projectileActive = false;
    this->activeProjectile = nullptr;
    this->projectileHit = false;
   

}

Tower::~Tower()
{
    for (auto& projectile : projectiles) {
        delete projectile;
    }
}

void Tower::setPosition(float x, float y)
{
    this->shape.setPosition(this->position.x = x, this->position.y = y);
    this->sprite.setPosition(this->position.x = x, this->position.y = y);
    
    // Œrodkowanie zasiegu wiezy
    this->rangeCoverage.setPosition(x + this->sprite.getGlobalBounds().width / 2 - this->rangeCoverage.getRadius(),
        y + this->sprite.getGlobalBounds().height / 2 - this->rangeCoverage.getRadius());

}

void Tower::detectEnemies() {
    auto& enemies = waveManager->getEnemies();
    for (const auto& enemy : enemies) {
       
        float distance = sqrt(pow(enemy->getPosition().x - this->getPosition().x, 2) +
            pow(enemy->getPosition().y - this->getPosition().y, 2));
        if (distance <= this->range) {
            this->targetEnemy = enemy;
            return;
        }
    }
    this->targetEnemy = nullptr;
}

void Tower::fire() {
    if (targetEnemy && !projectileActive && fireClock.getElapsedTime() >= fireInterval) {
        sf::Vector2f direction = targetEnemy->getPosition() - this->getPosition();
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length;

        this->activeProjectile = new Projectile(this->player, this->textureManager, sf::Vector2f(this->getPosition().x + 16.f, this->getPosition().y), direction, projectileSpeed);
        this->projectiles.push_back(activeProjectile);
        this->projectileActive = true;
        this->projectileHit = false;
        this->fireClock.restart(); // Zrestartuj zegar po strzale
    }
}


void Tower::updateProjectiles(const float& dt) {
    for (auto& projectile : projectiles) {
        projectile->update(dt);
    }
    // Usuwanie nieaktywnych pocisków
    for (auto it = projectiles.begin(); it != projectiles.end(); ) {
        Projectile* projectile = *it;
        bool remove = !projectile->isActive() || projectile->getPosition().x < 0 || projectile->getPosition().y < 0 ||
            projectile->getPosition().x > 1920 || projectile->getPosition().y > 1080;
        if (remove) {
            delete projectile;
            it = projectiles.erase(it); 
            if (projectile == activeProjectile) {
                projectileActive = false;
            }
        }
        else {
            ++it; // Przejœcie do nastêpnego elementu, jeœli nie usuwamy obecnego
        }
    }
}


Enemy* Tower::getEnemy()
{
    return this->targetEnemy;
}

int Tower::getTowerCost()
{
    return this->cost;
}



sf::Vector2f& Tower::getPosition()
{
    return this->position;
}

void Tower::toggleRangeVisibility() {
    this->showRange = !showRange; // Prze³¹czanie widocznoœci zasiêgu
}

void Tower::handleMouseInteraction(const sf::Vector2f& mousePos)
{
    if (this->sprite.getGlobalBounds().contains(mousePos)) {
        this->toggleRangeVisibility(); 
    }
}

void Tower::checkCollisions() {
    for (auto projectile : projectiles) {
        for (auto enemy : waveManager->getEnemies()) {
            if (projectile->getGlobalBounds().intersects(enemy->getGlobalBounds()) && !projectileHit) {
                projectile->changeActive(false); // Deaktywuj pocisk po trafieniu
                enemy->decreaseHealth(this->damage); // Wie¿a zadaje obra¿enia

                projectileHit = true; // Ustawienie flagi po trafieniu
                if (enemy->getHealth() <= 0) {
                    enemy->setAlive(false);
                    this->soundManager->getSound("TankExplosion").play();
                    
                    this->player->increaseScore(enemy->getScore());
                    
                    this->player->increaseCoins(enemy->getCoins());
                    killedEnemies.push_back(enemy);
                }
                break; // Przerwij pêtlê, poniewa¿ pocisk nie mo¿e trafiæ wiêcej ni¿ jednego przeciwnika
            }
        }
    }
}



std::vector<Enemy*> Tower::getKilledEnemies() {
    return this->killedEnemies;
}

void Tower::update(const float& dt)
{

    this->detectEnemies();
    if (targetEnemy) {
        this->fire();
    }
    this->checkCollisions();
    this->updateProjectiles(dt);

}

void Tower::render(sf::RenderTarget* target)
{
    target->draw(this->sprite);
    if (this->showRange) {
        target->draw(this->rangeCoverage);
    }

    for (auto projectile : projectiles) {
        projectile->render(target);
    }

 
}













