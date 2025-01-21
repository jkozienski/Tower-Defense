#include "Game.h"

void Game::initWindow() {
    this->window = new sf::RenderWindow(sf::VideoMode(1296, 720), "Tower Defense - JKozienski", sf::Style::None);
    if (!icon.loadFromFile("Img/GameIcon.png")) {
        std::cerr << "Nie wczytano Ikony Gry\n";
    }
    this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

}

void Game::initStates() {
    this->states.push(new MainMenu(this->window, &this->states, this->textureManager,this->soundManager));
}

void Game::initTextures()
{
    this->textureManager->loadTexture("GameStateBG", "Img/BGGameState2.png");
    this->textureManager->loadTexture("MainMenuBG", "Img/Menu.png");
    this->textureManager->loadTexture("HighScoresBG", "Img/HighScoresBG.png");
    this->textureManager->loadTexture("GameOver", "Img/GameOver.png");
    this->textureManager->loadTexture("PathTile", "Img/PathTile.png");

    this->textureManager->loadTexture("TankEasy", "Img/Enemy/Tank1.png");
    this->textureManager->loadTexture("TankMedium", "Img/Enemy/Tank2.png");
    this->textureManager->loadTexture("TankHard", "Img/Enemy/Tank3.png");

    this->textureManager->loadTexture("HPfull", "Img/HP/HPfull.png");
    this->textureManager->loadTexture("HPhalf", "Img/HP/HPhalf.png");
    this->textureManager->loadTexture("HPnull", "Img/HP/HPnull.png");

    this->textureManager->loadTexture("TurretLVL1", "Img/Turret/Turret1.png");
    this->textureManager->loadTexture("TurretLVL2", "Img/Turret/Turret2.png");
    this->textureManager->loadTexture("TurretLVL3", "Img/Turret/Turret3.png");
    this->textureManager->loadTexture("Projectile1", "Img/Turret/projectile1.png");


    this->textureManager->loadTexture("Coin", "Img/Coin/Coin.png");
    this->textureManager->loadTexture("PathTile", "Img/PathTile.png");
    this->textureManager->loadTexture("WaveIcon", "Img/WaveIcon.png");


}

void Game::initSounds()
{
    this->soundManager->loadSound("TankExplosion", "Resources/Sounds/large-explosion-2.wav");
    this->soundManager->loadSound("MainTheme", "Resources/Sounds/Battle of the Bytes.mp3");
    this->soundManager->loadSound("GameplayTheme", "Resources/Sounds/Battle Hymn of the Bitcrushers.mp3");
    this->soundManager->loadSound("GameoverTheme", "Resources/Sounds/Game Over.mp3");

    this->soundManager->loadSound("TowerBuy", "Resources/Sounds/money-bag.wav");
    this->soundManager->loadSound("ButtonClick", "Resources/Sounds/8-bit-damage.wav");
    this->soundManager->loadSound("Cancel", "Resources/Sounds/retro-video-game-sfx-ouch.wav");
    this->soundManager->loadSound("NextWave", "Resources/Sounds/buttonpress.wav");
}
Game::Game() {
    this->initSounds();
    this->initWindow();
   

    this->soundManager->getSound("MainTheme").play();
    this->soundManager->getSound("MainTheme").setLoop(1);

    this->initStates();
    this->initTextures();
}

Game::~Game() {
    delete this->window;
    delete this->textureManager;
    delete this->soundManager;
    delete this->button;

    while (!this->states.empty()) {
        delete this->states.top();
        this->states.pop();
    }
}

void Game::updateDt() {
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents() {
    while (this->window->pollEvent(this->sfEvent)) {
        if (this->sfEvent.type == sf::Event::Closed) {
            this->window->close();
        }
        
        if (!this->states.empty()) {
            this->states.top()->handleInput(this->sfEvent);
        };
        
    }
}

void Game::update() {
    this->updateSFMLEvents();

    if (!this->states.empty()) {
        this->states.top()->update(this->dt);

        if (this->states.top()->getQuit()) {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
            if (this->states.empty()) {
                this->states.push(new MainMenu(this->window, &this->states, this->textureManager, this->soundManager));
                
            }
            else if (this->states.top()->getMenuReturn()) {
                this->states.push(new MainMenu(this->window, &this->states, this->textureManager, this->soundManager));
               
            }
        }
    }
    else {
        this->window->close();
    }
}
void Game::render() {
    this->window->clear(sf::Color::Black);

    if (!this->states.empty()) {
        this->states.top()->render(this->window);
    }

    this->window->display();
}

void Game::run() {
    while (this->window->isOpen()) {
        this->updateDt();
        this->update();
        this->render();
    }
}
