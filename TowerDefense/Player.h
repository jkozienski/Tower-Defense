#pragma once
class Player
{
private:
    int health;
    int score;
    int coins;

public:
    Player(int health, int score, int coins);

    int getHealth() const;
    int getScore() const;
    int getCoins() const;

    void increaseHealth(int amount);
    void decreaseHealth(int amount);

    void increaseScore(int amount);

    void increaseCoins(int amount);
    void decreaseCoins(int amount);
};

