#pragma once
#include "State.h"
#include "GameOverState.h"
#include "MenuUI.h"
#include "MainMenu.h"
#include "Enemy.h"
#include "EnemyEasy.h"
#include "EnemyMedium.h"
#include "EnemyHard.h"
#include "GameplayUI.h"
#include "Projectile.h";
#include "Player.h"
#include "Map.h"
#include "Tower.h";
#include "TowerLow.h";
#include "TowerMid.h";
#include "TowerHigh.h";

#include <future>
#include <thread>
#include <mutex>
#include <chrono>

class GameState : public State
{
private:
	MenuUI* returnButton;
	Map* map;
	std::vector<Tower*> towers;
	Player* player;
	GameplayUI* gameplayUI;
	Projectile* projectile;
	WaveManager* waveManager;

	std::thread workThread;
	std::mutex workMtx;
	std::atomic<bool> running;
	bool gameOver = false;

	sf::Clock gameClock; // Zegar do œledzenia czasu trwania rozgrywki
	sf::Time gameDuration; // Przechowuje czas trwania rozgrywki
	std::future<void> asyncTimer; // Przechowuje obiekt std::async

public:
	GameState(sf::RenderWindow* window, std::stack<State*>* states, TextureManager* textureManager, SoundManager* soundManager);
	virtual ~GameState();

	void checkPlayerHP();
	void drawGameStateBG();

	void startTimer(); // Metoda do uruchomienia licznika czasu w tle
	void stopTimer(); // Metoda do zatrzymania licznika czasu
	void timerFunction(); // Funkcja licznika czasu
	
	sf::Time getElapsedTime() const;

	std::pair<int, int> getGameDuration() const;
	

	void endState();
	void updateKeybinds(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);

};

