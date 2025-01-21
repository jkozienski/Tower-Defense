#pragma once
#include "State.h"
#include "GameState.h"
#include "HighScoreState.h"
#include "OptionsState.h"
#include "MenuUI.h"


class MainMenu : public State
{
public:
	MainMenu(sf::RenderWindow* window, std::stack<State*>* states, TextureManager* textureManager, SoundManager* soundManager);
	~MainMenu();

	void drawMenuBG();
	void endState();
	void updateButtons();
	void updateKeybinds(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);

};

