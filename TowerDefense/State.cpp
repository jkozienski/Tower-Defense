#include "State.h"

State::State(sf::RenderWindow* window, std::stack<State*>* states, TextureManager* textureManager, SoundManager* soundManager) : window(window),states(states), textureManager(textureManager), soundManager(soundManager)
{
	
	this->quit = false;
	this->menuReturn = false;
}

State::~State() = default;



const bool& State::getQuit() const
{
	return this->quit;
}

const bool& State::getMenuReturn() const
{
	return this->menuReturn;
}




void State::checkForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		this->quit = true;
	}

}




void State::updateMousePos()
{
	this->TEMPmousePos = sf::Mouse::getPosition(*this->window);
	this->mousePos.x = TEMPmousePos.x;
	this->mousePos.y = TEMPmousePos.y;
	//std::cout << mousePos.x << " " << mousePos.y << "\n";

}

