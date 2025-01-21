#pragma once
#include "State.h"
class MainMenuState : public State
{
private:
	std::stack<State*>* states;
	
	MenuUI* button;

public:
	MainMenuState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~MainMenuState();

	
	void endState();
	void updateButtons();
	void updateKeybinds(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);

};

