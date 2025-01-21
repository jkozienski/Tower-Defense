#pragma once
#include "State.h"
#include "MenuUI.h"
#include <filesystem>
#include <ranges>


class HighScoresState : public State {
private:
    MenuUI* returnButton;
    std::vector<std::tuple<std::string, int, int, int>> highScores;
    sf::Font font;
    sf::Text mainText;

    void loadAndSortScores();
public:
    HighScoresState(sf::RenderWindow* window, std::stack<State*>* states, TextureManager* textureManager, SoundManager* soundManager);
    virtual ~HighScoresState();

    void initMainText();
    void initFont();
    void endState() override;
    void updateKeybinds(const float& dt) override;
    void drawBackGround();
    void update(const float& dt) override;
    void render(sf::RenderTarget* target = nullptr) override;
};
