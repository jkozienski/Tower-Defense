#pragma once
#include "State.h"
#include "MenuUI.h"

class OptionsState : public State {
private:
    MenuUI* returnButton;
    MenuUI* volumeUpButton;    
    MenuUI* volumeDownButton; 
    sf::Text audioText;
    sf::Text optionText;

    sf::Font font;
    float volumeLevel ;         // Aktualny poziom g³oœnoœci

    void initFont();
    void initAudioText();

    void initOptionText();



public:
    OptionsState(sf::RenderWindow* window, std::stack<State*>* states, TextureManager* textureManager, SoundManager* soundManager);
    virtual ~OptionsState();

    void endState() override;
    void updateKeybinds(const float& dt) override;
    void drawBackGround();
    void update(const float& dt) override;
    void render(sf::RenderTarget* target = nullptr) override;
};
