#pragma once
#include <cmath>
#include <thread>
#include <mutex>

#include <SFML/Graphics.hpp>

#include "Map.h"
#include "TextureManager.h"
#include "Player.h"

class Enemy {
protected:
	sf::RectangleShape shape;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f position;
	sf::Vector2f positionCentre;

	TextureManager* textureManager;
	Map* map;
	Player* player;

	int health;
	int maxHealth;
	int damage;
	float speed;

	bool isAlive = true;
	bool isFinished = false;

	float currentDelay;
	//float movementDelay;

	float movementSpeed;
	bool movedRight = false;
	bool movedUp = false;
	bool movedDown = false;

	int coins;
	int score;
	bool showHP = false;



public:
	Enemy(const sf::Vector2f& startPos, int health, int maxHealth, int damage, float speed, int coins, int score, Map* map, TextureManager* textureManager, Player* player);
	~Enemy();

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target) = 0;

	const sf::Vector2f& getPosition() const;
	int getHealth() const;
	int getDamage() const;
	float getSpeed() const;
	int getCoins() const;
	int getScore() const;
	const bool& getAlive() const;
	const bool& getFinished() const;
	const sf::RectangleShape& getShape() const;
	void setPosition(sf::Vector2f& position);
	void setHealth(int newHealth);
	void decreaseHealth(int amount);


	void setDamage(int newDamage);
	void setSpeed(float newSpeed);
	void setAlive(bool newAlive);
	void toggleHealthVisibility();
	void handleMouseInteraction(const sf::Vector2f& mousePos);
	sf::FloatRect getGlobalBounds() const;
	void moveToNextTile(const Map* map,const float& dt);


};