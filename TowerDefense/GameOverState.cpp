#include "GameOverState.h"



GameOverState::GameOverState(sf::RenderWindow* window, std::stack<State*>* states, TextureManager* textureManager, Player* player, SoundManager* soundManager, int minutes, int seconds)
    : State(window, states, textureManager, soundManager) {

    this->background.setTexture(this->textureManager->getTexture("GameOver"));
    this->player = player;

    this->font.loadFromFile("Resources\\Fonts\\04B_30__.ttf");
    gameOverText.setFont(font);
    gameOverText.setString("Game Over!");
    gameOverText.setCharacterSize(80);
    //gameOverText.setColor(color);
    gameOverText.setPosition(window->getSize().x / 2 - gameOverText.getLocalBounds().width / 2, window->getSize().y / 3);

    namePromptText.setFont(font);
    namePromptText.setString("Enter your name:");
    namePromptText.setCharacterSize(24);
    namePromptText.setFillColor(sf::Color::Black);
    namePromptText.setPosition(window->getSize().x / 2 - namePromptText.getLocalBounds().width / 2, window->getSize().y / 2);

    playerNameText.setFont(font);
    playerNameText.setCharacterSize(24);
    playerNameText.setFillColor(sf::Color::Black);
    playerNameText.setPosition(window->getSize().x / 2 - 100, window->getSize().y / 2 + 30);

    quitButton = new MenuUI(sf::Vector2f(200, 50), sf::Vector2f(window->getSize().x * 0.405f, window->getSize().y * 0.73f), sf::Color::Red, "Submit");

    this->durationText.setFont(this->font);
    this->durationText.setCharacterSize(40);
    this->durationText.setFillColor(sf::Color::Black);
    this->durationText.setPosition(this->window->getSize().x * 0.35f, this->window->getSize().y * 0.61f);
    this->minutes = minutes;
    this->seconds = seconds;
    this->durationText.setString("Time: " + std::to_string(this->minutes) + "m " + std::to_string(this->seconds) + "s");

}

GameOverState::~GameOverState() {
    delete this->quitButton;
    delete this->soundManager; 
    delete this->textureManager;
    delete this->player;
}

//TODO:Regex
bool GameOverState::isValidPlayerName(const std::string& name) {
    std::regex pattern("^[a-zA-Z0-9]{1,16}$"); // od 1 do 20 znaków alfanumerycznych
    return std::regex_match(name, pattern);
}

void GameOverState::savePlayerScore(const std::string& name, int score,int minutes, int seconds)
{
    std::ofstream outFile("HighsSores.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << name << " " << score << " " << minutes << " " << seconds << "\n";
        outFile.close();
    }
}

void GameOverState::endState() {
    this->soundManager->getSound("GameoverTheme").stop();
    this->soundManager->getSound("MainTheme").play();

    this->quit = true;
    this->menuReturn = true;
    this->states->push(new MainMenu(this->window, this->states, this->textureManager, this->soundManager));
}

void GameOverState::updateKeybinds(const float& dt) {
    this->checkForQuit();
}

void GameOverState::handleInput(sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        //std::cout << "Wpisano: " << event.text.unicode << std::endl; // Debugging
        if (event.text.unicode == '\b' && !playerName.empty()) {
            playerName.pop_back();
        }
        else if (event.text.unicode != '\b') {
            std::string tempName = playerName + static_cast<char>(event.text.unicode);
            //TODO:Regex
            if (isValidPlayerName(tempName)) {
                this->playerName += static_cast<char>(event.text.unicode);
            }
            else {
                this->soundManager->getSound("Cancel").play();
            }
        }
    }
}

void GameOverState::update(const float& dt) {
    this->updateMousePos();
    quitButton->update(this->mousePos);

    if (quitButton->isPressed()) {
        this->savePlayerScore(this->playerName, this->player->getScore(), this->minutes, this->seconds);
        this->endState();
        
    }
    this->playerNameText.setString(playerName);
}

void GameOverState::render(sf::RenderTarget* target) {
    if (!target) {
        target = this->window;
    }
    this->window->clear(sf::Color::Black);
    target->draw(this->background);
    target->draw(gameOverText);
    target->draw(namePromptText);
    target->draw(playerNameText);
    quitButton->render(target);
    target->draw(this->durationText);

}
