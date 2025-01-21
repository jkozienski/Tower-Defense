#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <unordered_map>

#include "Projectile.h"
#include "Player.h"
#include "Map.h"
#include "TextureManager.h"
#include "WaveManager.h"


#include "Tower.h";
#include "TowerLow.h";
#include "TowerMid.h";
#include "TowerHigh.h";



class GameplayUI {
private:
    sf::Font font;
    sf::Text playerCoinsText;
    sf::Text coinAmount;
    sf::Text playerHealthText;
    sf::Text turretBuyMenuText;
    sf::Text waveNumberText;
    sf::Text startGameText;
    sf::Text waveNumber;
    sf::Text playerScore;
    sf::Text scoreText;
    std::vector<sf::Text> turretCostText;

    std::vector<sf::Sprite> coinSprite;
    std::vector<sf::Sprite> healthSprites;
    std::vector<sf::Sprite> turretSprites;
    std::vector<sf::Sprite> pathSprite;
    sf::Sprite waveIconSprite;


    sf::RenderWindow* window;
    sf::Vector2i TEMPmousePos;
    sf::Vector2f mousePos;
    bool mouseLeftPressedLastFrame = false;  
    bool mouseLeftPressed = false;          
    bool mouseRightPressedLastFrame = false;
    bool mouseRightPressed = false;

    bool isTurretSelected;
    WaveManager* waveManager;
    Projectile* projectile;
    Player* player;
    Map* map;
    TextureManager* textureManager;
    SoundManager* soundManager;
    std::vector<Tower*> menuTowers;
    std::vector<Tower*> mapTowers;
    Tower* selectedTower;
    Tower* selectedTowerTMP = nullptr;  // Nowy wskaünik do tymczasowej instancji wiezy
    
    bool isHoveringIcon=false;

    void initFont();
    void initTexts();
    void initHealthSprites();
    void initTurretSprites();
    void initCoinSprite();
    void initWaveSprite();
    bool isTowerSelected()const;


public:
    GameplayUI(sf::RenderWindow* window,TextureManager* textureManager, SoundManager* soundManager,WaveManager* waveManager, Player* player, Map* map, Projectile* projectile);
    virtual ~GameplayUI();

    void updateMousePos();
    void updateMouseState();
    bool RightMouseClick();
    Tower* getMenuTowers(int number)const;
    void updateCoinAmount();
    void updateHealth();
    void buyTower();
    const bool& turretSelected() const;
    void handleTowerSelection();
    void checkWaveButton();
    std::vector<sf::Sprite>* getTurretSprite();

    void update(const float& dt);
    void render(sf::RenderTarget* target);
    
    const TextureManager* getTxtMan();
};
