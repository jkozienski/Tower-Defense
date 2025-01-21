#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "GameState.h"
#include "MainMenu.h"
//#include "GameOverState.h"
//#include "HighScoreState.h"
//#include "OptionsState.h"

#include <windows.h>
#include "resource.h"


class Game
{
private:

protected:
	TextureManager* textureManager;
	SoundManager* soundManager;
	sf::Image icon;
	sf::RenderWindow *window;
	sf::Event sfEvent;

	sf::Clock dtClock;		
	float dt;
	
	MenuUI* button;

	std::stack<State*> states;


	void initWindow();
	void initStates();
	void initTextures();
	void initSounds();



public:
	Game();
	~Game();

	void updateDt();
	void updateSFMLEvents();
	void update();

	void render();
	void run();

};

