#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states) : State(window)
{
	this->window = window;
	this->states = states;
	
	this->button = new MenuUI(window);
	std::cout << "MMS: " << window << "\n";

}

MainMenuState::~MainMenuState()
{
}


void MainMenuState::endState()
{
	std::cout << "Koniec stanu MainMenuState\n";
	this->getQuit();
}


void MainMenuState::updateKeybinds(const float& dt)
{
	this->checkForQuit();
	
}

void MainMenuState::updateButtons()
{
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePos();
	//std::cout << this->mousePos.x << "  " << mousePos.y << "\n"; //Wyswietla pozycje myszki

	this->button->update(dt);
	

	this->updateKeybinds(dt);
	this->checkForQuit();
	//std::cout << "MainMenuState\n";
}

void MainMenuState::render(sf::RenderTarget* target)
{
	/// Upewnij siê, ¿e cel renderowania jest ustawiony na okno docelowe
	if (!target) {
		target = this->window;
	}
	
	/// Utwórz kwadrat
	this->window->clear(sf::Color::Red);

	

	button->render(window);



}


