#include "HighScoreState.h"

HighScoresState::HighScoresState(sf::RenderWindow* window, std::stack<State*>* states, TextureManager* textureManager, SoundManager* soundManager) : State(window, states, textureManager,soundManager) {
    returnButton = new MenuUI(sf::Vector2f(410, 48), sf::Vector2f(1000, 600),
        sf::Color::Black, "Return");

    this->loadAndSortScores();

    this->initFont();
    this->initMainText();
}

HighScoresState::~HighScoresState() {
    delete this->returnButton;
    delete this->soundManager;
    delete this->textureManager;
}

void HighScoresState::loadAndSortScores()
{
    if (!std::filesystem::exists("HighsSores.txt")) {
        std::ofstream outFile("HighsSores.txt");
    }
    std::ifstream inFile("HighsSores.txt");
    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string name;
        int score;
        int minutes;
        int seconds;
        if (iss >> name >> score >> minutes >> seconds) {
            highScores.emplace_back(name, score, minutes, seconds);
        }
    }

    std::sort(highScores.begin(), highScores.end(), [](const std::tuple<std::string, int, int, int>& a, const std::tuple<std::string, int, int, int>& b) {
        return std::get<1>(b) < std::get<1>(a);
        });
}

void HighScoresState::initFont() {
    if (!this->font.loadFromFile("Resources/Fonts/04B_30__.ttf")) {
        std::cout << "Nie zaladowano fontu!!!\n";
    }
}

void HighScoresState::initMainText()
{
    this->mainText.setString("Leaderboard");
    this->mainText.setFont(this->font);
    this->mainText.setCharacterSize(80);
    this->mainText.setFillColor(sf::Color::Black);

    sf::Vector2u windowSize = this->window->getSize();
    this->mainText.setPosition(windowSize.x * 0.22f, windowSize.y*0.07f);
}

void HighScoresState::endState() {
    this->quit = true;
    this->menuReturn = true;
}

void HighScoresState::updateKeybinds(const float& dt) {
    this->checkForQuit();
}

void HighScoresState::drawBackGround()
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

void HighScoresState::update(const float& dt) {
    this->updateMousePos();
    this->returnButton->update(this->mousePos);

    if (this->returnButton->isPressed()) {
        this->soundManager->getSound("ButtonClick").play();
        this->endState();
        
    }
}

void HighScoresState::render(sf::RenderTarget* target) {
    if (!target) {
        target = this->window;
    }

    this->window->clear(sf::Color::Black);
    this->drawBackGround();
  
    returnButton->render(target);
    target->draw(this->mainText);


    sf::Text scoreText;
    scoreText.setFont(this->font);
    int size = 36;
    scoreText.setCharacterSize(size);
    scoreText.setFillColor(sf::Color::Yellow);
    float yOffset = 200.0f;


    //TODO:Ranges
    auto topScores = highScores | std::views::take(8);
    for (const auto& score : topScores) {
        std::string displayText = std::get<0>(score) + " - " + std::to_string(std::get<1>(score)) + ", " +
            std::to_string(std::get<2>(score)) + "m " + std::to_string(std::get<3>(score)) + "s ";
       
        scoreText.setString(displayText);
        scoreText.setPosition(this->window->getSize().x / 2 - scoreText.getLocalBounds().width / 2, yOffset);
        target->draw(scoreText);
        yOffset += 45.0f;
        if (size > 25.f) {
            size -= 4.f;
            scoreText.setFillColor(sf::Color::Black);
            scoreText.setCharacterSize(size);
        }
    }
}
