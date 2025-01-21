#include "MainMenu.h"



MainMenu::MainMenu(sf::RenderWindow* window, std::stack<State*>* states, TextureManager* textureManager, SoundManager* soundManager) : State(window,states,textureManager, soundManager)
{
	//Init MenuUI
	{
		this->button["Start_Game"] = new MenuUI(sf::Vector2f(410, 48), sf::Vector2f(this->window->getSize().x * 0.6527f,this->window->getSize().y * 0.555f),
			 sf::Color::Black, "Start Game");

		this->button["Options"] = new MenuUI(sf::Vector2f(410, 48), sf::Vector2f(this->window->getSize().x * 0.6527f, this->window->getSize().y * 0.638888f),
			 sf::Color::Black, "Options");

		this->button["High_Scores"] = new MenuUI(sf::Vector2f(410, 48), sf::Vector2f(this->window->getSize().x * 0.6527f, this->window->getSize().y * 0.721f),
			 sf::Color::Black, "High Scores");

		this->button["Quit"] = new MenuUI(sf::Vector2f(410, 48), sf::Vector2f(this->window->getSize().x * 0.6527f, this->window->getSize().y * 0.804f),
			 sf::Color::Black, "Quit");
	}

	

}

MainMenu::~MainMenu()
{
	delete this->button["Quit"];
	delete this->button["High_Scores"];
	delete this->button["Options"];
	delete this->button["Start_Game"];

	delete this->soundManager;
	delete this->textureManager;
}


void MainMenu::drawMenuBG()
{
	sf::Sprite background(this->textureManager->getTexture("MainMenuBG"));
	
	sf::Vector2u textureSize = this->textureManager->getTexture("MainMenuBG").getSize();

	sf::Vector2u windowSize = this->window->getSize();

	float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
	float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

	float scale = std::min(scaleX, scaleY);

	background.setScale(scale, scale);

	background.setPosition((windowSize.x - textureSize.x * scale) / 2, (windowSize.y - textureSize.y * scale) / 2);
		
	this->window->draw(background);
}

void MainMenu::endState()
{
	//std::cout << "Koniec stanu MainMenu\n";
	this->quit = true;
}


void MainMenu::updateKeybinds(const float& dt)
{
	this->checkForQuit();

}

void MainMenu::updateButtons()
{
	
	if (this->button["Start_Game"]->isPressed()) {
		//std::cout << "Start Gry\n";
		this->soundManager->getSound("ButtonClick").play();

		this->soundManager->getSound("MainTheme").stop();
		this->states->pop();
		this->states->push(new GameState(this->window, this->states, this->textureManager,this->soundManager));
	}
	else if (this->button["Options"]->isPressed()) {
		this->soundManager->getSound("ButtonClick").play();

		this->states->pop();
		this->states->push(new OptionsState(this->window, this->states, this->textureManager, this->soundManager));
	}
	else if (this->button["High_Scores"]->isPressed()) {
		this->soundManager->getSound("ButtonClick").play();

		this->states->pop();
		this->states->push(new HighScoresState(this->window, this->states, this->textureManager, this->soundManager));
	}

	else if (this->button["Quit"]->isPressed()) {
		this->soundManager->getSound("ButtonClick").play();

		this->window->close();
	} 
}

void MainMenu::update(const float& dt)
{
	this->updateMousePos();
	for (auto it : this->button) {
		it.second->update(this->mousePos);
	}

	this->updateKeybinds(dt);
	this->updateButtons();
	this->checkForQuit();

}

void MainMenu::render(sf::RenderTarget* target)
{
	/// cel renderowania jest ustawiony na okno docelowe
	if (!target) {
		target = this->window;
	}
	/// Wyczyœæ ekran
	this->window->clear(sf::Color::Black);


	this->drawMenuBG();

	// Renderuj przyciski
	for (auto it : this->button) {
		it.second->render(target);
	}
}


