#pragma once
#include "State.h"
#include "MenuUI.h"
#include "MainMenu.h"
#include <regex>

class GameOverState : public State {
private:
    MenuUI* quitButton;
    Player* player;
    sf::Text gameOverText;
    sf::Font font;
    sf::Text namePromptText; 
    sf::Text playerNameText;
    sf::Text durationText; 

    std::string playerName; 
    sf::Sprite background;
    int minutes;
    int seconds;
    bool isValidPlayerName(const std::string& name);
    void savePlayerScore(const std::string& name, int score,int minutes, int seconds);
public:
    GameOverState(sf::RenderWindow* window, std::stack<State*>* states, TextureManager* textureManager, Player* player, SoundManager* soundManager,int minutes,int seconds);
    virtual ~GameOverState();

    void endState() override;
    void updateKeybinds(const float& dt) override;
    void handleInput(sf::Event& event) override; // Obs³uga zdarzeñ wejœcia
    void update(const float& dt) override;
    void render(sf::RenderTarget* target = nullptr) override;
};
