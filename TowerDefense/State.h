#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <stack>
#include <map>

#include "MenuUI.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "WaveManager.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>


class State
{
private:

protected:
	TextureManager* textureManager;
	SoundManager* soundManager;
	MenuUI* menuUI;
	sf::RenderWindow* window;
	bool quit;
	bool menuReturn;
	sf::Vector2i TEMPmousePos;
	sf::Vector2f mousePos;



	std::stack<State*>* states;

	std::map<std::string, MenuUI*> button;

public:
	State(sf::RenderWindow* window, std::stack<State*>* states, TextureManager* textureManager, SoundManager* soundManager);
	virtual ~State();
	

	const bool& getQuit() const;
	const bool& getMenuReturn() const;

	virtual void endState() = 0;
	virtual void checkForQuit();
	virtual void handleInput(sf::Event& event) {};
	virtual void updateMousePos();
	virtual void updateKeybinds(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

