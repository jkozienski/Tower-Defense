#pragma once
#include "Enemy.h"

class EnemyMedium : public Enemy {
public:
    // Konstruktor
    EnemyMedium(const sf::Vector2f& startPos, int health, int maxHealth,
        int damage, float speed, int coins, int score, Map* map, TextureManager* textureManager, Player* player);


    // Nadpisane metody
    
    void update(const float& dt) override;
    void render(sf::RenderTarget* target) override;


};
