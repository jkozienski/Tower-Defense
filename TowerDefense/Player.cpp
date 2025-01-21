#include "Player.h"

Player::Player(int health, int score, int coins ) : health(health), score(score), coins(coins) {

}

int Player::getHealth() const {
    return health;
}

int Player::getScore() const {
    return score;
}

int Player::getCoins() const {
    return coins;
}

void Player::increaseHealth(int amount) {
    health += amount;
}

void Player::decreaseHealth(int amount) {
    
    health -= amount;
    if (health < 0) {
        health = 0;
    }
}

void Player::increaseScore(int amount) {
    score += amount;
}

void Player::increaseCoins(int amount) {
    coins += amount;
}

void Player::decreaseCoins(int amount) {
    coins -= amount;
    if (coins < 0) {
        coins = 0;
    }
}