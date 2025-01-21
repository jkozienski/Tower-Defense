#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states, TextureManager* textureManager, SoundManager* soundManager) : State(window, states,textureManager,soundManager) { // Inicjalizacja pola states w konstruktorze
	
	this->returnButton = new MenuUI(sf::Vector2f(1, 1), sf::Vector2f(5.f, -2.f),
		sf::Color::Red, "X");

	this->player = new Player(10, 0, 500);

	this->map = new Map("map.txt",48.f,48.f,this->textureManager);
	
	this->waveManager = new WaveManager(this->map,this->player);

	this->gameplayUI = new GameplayUI(this->window, this->textureManager,this->soundManager,this->waveManager ,this->player,this->map,this->projectile);

	this->running = true;
	workThread = std::thread(&GameState::checkPlayerHP, this);
	this->startTimer();

	this->soundManager->getSound("MainTheme").stop();

	this->soundManager->getSound("GameplayTheme").play();
	this->soundManager->getSound("GameplayTheme").setLoop(1);

} 



GameState::~GameState() {

	
	this->stopTimer();
	if (this->workThread.joinable()) {
		this->workThread.join();
	}
	delete this->map;
	delete this->player;
	delete this->waveManager;
	delete this->soundManager;

	for (auto tower : towers) {
		delete tower;
	}

}

//TODO:W¹tek asynchroniczny
void GameState::startTimer() {
	this->asyncTimer = std::async(std::launch::async, &GameState::timerFunction, this);
}

void GameState::stopTimer() {
	this->running = false;
	if (this->asyncTimer.valid()) {
		this->asyncTimer.get();
	}
}

void GameState::timerFunction() {
	while (this->running) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		this->gameDuration += sf::seconds(1);
	}
}

//sf::Time GameState::getElapsedTime() const {
//	return this->gameDuration;
//}

std::pair<int, int> GameState::getGameDuration() const {
	int minutes = this->gameDuration.asSeconds() / 60;
	int seconds = static_cast<int>(this->gameDuration.asSeconds()) % 60;
	return std::make_pair(minutes, seconds);
}

//TODO:W¹tek
void GameState::checkPlayerHP()
{
	while (running) {
		std::this_thread::sleep_for(std::chrono::seconds(1));  // sprawdza co 1 sekunde

		if (this->player->getHealth() <= 0) {
			this->running = false;
			this->gameOver = true;
		}
	}
}

void GameState::drawGameStateBG()
{

	sf::Sprite background(this->textureManager->getTexture("GameStateBG"));

	sf::Vector2u textureSize = this->textureManager->getTexture("GameStateBG").getSize();

	sf::Vector2u windowSize = this->window->getSize();

	float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
	float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

	float scale = std::min(scaleX, scaleY);

	background.setScale(scale, scale);

	background.setPosition((windowSize.x - textureSize.x * scale) / 2, (windowSize.y - textureSize.y * scale) / 2);

	this->window->draw(background);

}




void GameState::endState()
{
	//std::cout << "Koniec stanu GameState\n";
	this->quit = true;
	this->menuReturn = true;
}

void GameState::updateKeybinds(const float& dt)
{
	this->checkForQuit(); 

}

void GameState::update(const float& dt)
{
	this->updateMousePos();
	this->updateKeybinds(dt);

	returnButton->update(this->mousePos);
	if (returnButton->isPressed()) {
		this->soundManager->getSound("ButtonClick").play();
		this->soundManager->getSound("GameplayTheme").stop();
		this->soundManager->getSound("MainTheme").play();
		this->soundManager->getSound("MainTheme").setLoop(1);

		this->endState(); // tu ustawiam flagi quit na true
	}

	this->map->update(dt);

	//tu updateuje przeciwnikow
	this->waveManager->update(dt);
	for (auto& enemy : this->waveManager->getEnemies()) {
		enemy->handleMouseInteraction(this->mousePos);
		
	}

	//tu updateuje wieze
	this->gameplayUI->update(dt);

	if (gameOver) {
		this->soundManager->getSound("GameplayTheme").stop();
		this->soundManager->getSound("GameoverTheme").play();
		this->soundManager->getSound("GameoverTheme").setLoop(1);


		this->states->pop();
		this->states->push(new GameOverState(this->window, this->states, this->textureManager, this->player, this->soundManager, this->gameDuration.asSeconds() / 60, static_cast<int>(this->gameDuration.asSeconds()) % 60));
	}

}

void GameState::render(sf::RenderTarget* target)
{
	//  cel renderowania ustawiony na okno docelowe
	if (!target) {
		target = this->window;
	}

	this->window->clear(sf::Color::Black);

	this->drawGameStateBG();
	returnButton->render(target);
	this->map->render(this->window);

	this->waveManager->render(this->window);

	for (auto tower : towers) {
		tower->render(this->window);
	}

	this->gameplayUI->render(target);


}

