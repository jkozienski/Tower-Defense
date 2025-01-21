#include "OptionsState.h"

OptionsState::OptionsState(sf::RenderWindow* window, std::stack<State*>* states, TextureManager* textureManager, SoundManager* soundManager)
    : State(window, states, textureManager,soundManager) {
    returnButton = new MenuUI(sf::Vector2f(410, 48), sf::Vector2f(this->window->getSize().x*0.765f, this->window->getSize().y * 0.835f), sf::Color::Red, "Return");
    volumeUpButton = new MenuUI(sf::Vector2f(50, 50), sf::Vector2f(this->window->getSize().x * 0.34f, this->window->getSize().y * 0.3f), sf::Color::Green, "+");
    volumeDownButton = new MenuUI(sf::Vector2f(50, 50), sf::Vector2f(this->window->getSize().x * 0.28f, this->window->getSize().y * 0.3f), sf::Color::Green, "-");
    this->initFont();
    this->initAudioText();
    this->initOptionText();
    this->volumeLevel = this->soundManager->getSound("Cancel").getVolume();
   
}


OptionsState::~OptionsState() {
    delete this->returnButton;
    delete this->volumeUpButton;
    delete this->volumeDownButton;
}



void OptionsState::initAudioText()
{
    this->audioText.setString("Audio: ");
    this->audioText.setFont(this->font);
    this->audioText.setCharacterSize(48);
    this->audioText.setFillColor(sf::Color::Black);

    
    this->audioText.setPosition(this->window->getSize().x * 0.1f, this->window->getSize().y * 0.3f);
}

void OptionsState::initOptionText()
{
    this->optionText.setString("OPTIONS");
    this->optionText.setFont(this->font);
    this->optionText.setCharacterSize(60);
    this->optionText.setFillColor(sf::Color::Black);


    this->optionText.setPosition(this->window->getSize().x * 0.35f, this->window->getSize().y * 0.1f);
}

void OptionsState::initFont()
{
    if (!this->font.loadFromFile("Resources/Fonts/04B_30__.ttf")) {
        std::cout << "Nie zaladowano fontu!!!\n";
    }
}

void OptionsState::endState() {
    std::cout << "Koniec options";
    this->quit = true;
}

void OptionsState::updateKeybinds(const float& dt) {
    this->checkForQuit();
}

void OptionsState::drawBackGround()
{
    sf::Sprite background(this->textureManager->getTexture("HighScoresBG"));

    sf::Vector2u textureSize = this->textureManager->getTexture("HighScoresBG").getSize();

    sf::Vector2u windowSize = this->window->getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    float scale = std::min(scaleX, scaleY);

    background.setScale(scale, scale);

    background.setPosition((windowSize.x - textureSize.x * scale) / 2, (windowSize.y - textureSize.y * scale) / 2);

    this->window->draw(background);
}

void OptionsState::update(const float& dt) {
    this->updateMousePos();
    returnButton->update(this->mousePos);
    volumeUpButton->update(this->mousePos);
    volumeDownButton->update(this->mousePos);

    if (returnButton->isPressed()) {

        this->soundManager->getSound("ButtonClick").play();

        this->endState();
    }

    if (volumeUpButton->isPressed()) {
        volumeLevel = volumeLevel + 0.02f;
        if (volumeLevel >= 100.f) {
            volumeLevel = 100.f;
            this->soundManager->getSound("Cancel").play();
        }

        for (auto& soundPair : soundManager->getSounds()) {
            soundPair.second.setVolume(volumeLevel);
        }
    }

    if (volumeDownButton->isPressed()) {
        volumeLevel = volumeLevel - 0.02f;  
        if (volumeLevel <= 0.f) {
            this->soundManager->getSound("Cancel").setVolume(80.f);
            this->soundManager->getSound("Cancel").play();
            volumeLevel = 0.f;
        }
        for (auto& soundPair : soundManager->getSounds()) {
            soundPair.second.setVolume(volumeLevel);
        }
    }
}

void OptionsState::render(sf::RenderTarget* target) {
    if (!target) {
        target = this->window;
    }

    this->window->clear(sf::Color::Black); // Czyszczenie t³a
    this->drawBackGround();
    this->returnButton->render(target); 
    this->volumeUpButton->render(target); 
    this->volumeDownButton->render(target); 
    target->draw(this->audioText);
    target->draw(this->optionText);

}
