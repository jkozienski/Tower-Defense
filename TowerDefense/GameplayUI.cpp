#include "GameplayUI.h"

GameplayUI::GameplayUI(sf::RenderWindow* window, TextureManager* textureManager, SoundManager* soundManager,WaveManager* waveManager, Player* player, Map* map, Projectile* projectile)
    : window(window), textureManager(textureManager),soundManager(soundManager), waveManager(waveManager), player(player), map(map), projectile(projectile), isTurretSelected(false) {
    
    this->initFont();
    this->initTexts();
    this->initHealthSprites();
    this->initCoinSprite();
    this->initWaveSprite();

   // this->projectile = new Projectile(this->player);
    


    TowerLow* towerLow = new TowerLow(5.0f,this->textureManager,this->soundManager,this->waveManager,this->player, 1, 0, 50);
    TowerMid* towerMid = new TowerMid(5.0f, this->textureManager, this->soundManager, this->waveManager, this->player, 1, 0, 125);
    TowerHigh* towerHigh = new TowerHigh(5.0f, this->textureManager, this->soundManager, this->waveManager, this->player, 1, 0, 225);
    
    menuTowers.push_back(towerLow);
    menuTowers.push_back(towerMid);
    menuTowers.push_back(towerHigh);

    this->initTurretSprites();
}

GameplayUI::~GameplayUI() {
    delete this->soundManager;
    delete this->textureManager;
    delete this->map;
    delete this->player;
    delete this->projectile;
    delete this->waveManager;
    delete this->selectedTower;

    for (auto& tower : mapTowers) {
        delete tower;
    }
    for (auto& tower : menuTowers) {
        delete tower;
    }
}

void GameplayUI::updateMousePos()
{
    this->TEMPmousePos = sf::Mouse::getPosition(*this->window);
    this->mousePos.x = TEMPmousePos.x;
    this->mousePos.y = TEMPmousePos.y;
}

void GameplayUI::updateMouseState()
{
    mouseLeftPressedLastFrame = mouseLeftPressed;
    mouseLeftPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    mouseRightPressedLastFrame = mouseRightPressed;
    mouseRightPressed = sf::Mouse::isButtonPressed(sf::Mouse::Right);
}

bool GameplayUI::RightMouseClick()
{
    return mouseRightPressedLastFrame && !mouseRightPressed;
}

Tower* GameplayUI::getMenuTowers(int number) const
{
    return menuTowers[number];
}


void GameplayUI::updateCoinAmount()
{
    this->coinAmount.setString(std::to_string(this->player->getCoins()));

    //zablokowanie kupna innej wiezy gdy ma sie juz jedna w rece
    if (isTowerSelected()) {
        return;
    }
        

    for (size_t i = 0; i < menuTowers.size(); ++i) {
        auto& tower = this->menuTowers[i]->sprite;
        if (tower.getGlobalBounds().contains(mousePos)) {
            if (this->turretSelected()) {
                int turretCost = std::stoi(this->turretCostText[i].getString().toAnsiString());
                if (this->player->getCoins() >= turretCost) {
                    this->selectedTower = this->menuTowers[i]; // Zapisz wybran¹ wie¿ê
                    this->isTurretSelected = true;
                    this->player->decreaseCoins(turretCost);

                }
            }
        }
    }
}

void GameplayUI::updateHealth()
{
    // Aktualizacja sprite serc na podstawie zdrowia 
    int health = this->player->getHealth();
    for (int i = 0; i < 5; ++i) {
        if (health >= 2) {
            this->healthSprites[i].setTexture(this->textureManager->getTexture("HPfull"));
            health -= 2;

        }
        else if (health == 1) {
            this->healthSprites[i].setTexture(this->textureManager->getTexture("HPhalf"));

            health -= 1;
        }
        else {

            this->healthSprites[i].setTexture(this->textureManager->getTexture("HPnull"));
        }
    }

}

void GameplayUI::buyTower() {
    if (isTurretSelected) {
        if (turretSelected()) {
          
            int gridX = mousePos.x / map->getWidthTile();
            int gridY = mousePos.y / map->getHeightTile();
         
            // Sprawdzenie, czy pole jest wolne
            bool areaFree = true;
            for (const auto& tower : mapTowers) {
                if (tower->sprite.getGlobalBounds().intersects(sf::FloatRect(gridX * map->getWidthTile(), gridY * map->getHeightTile(), map->getWidthTile(), map->getHeightTile()))) {
                    areaFree = false;
                    break;
                }
            }
            if (areaFree) {
                if (selectedTower == this->menuTowers[0]) {
                    selectedTowerTMP = new TowerLow(550.0f, this->textureManager, this->soundManager, this->waveManager, this->player, 3, 120, 50);
                }
                else if (selectedTower == this->menuTowers[1]) {
                    selectedTowerTMP = new TowerMid(550.0f, this->textureManager, this->soundManager, this->waveManager, this->player, 4, 135, 125);
                }
                else if (selectedTower == this->menuTowers[2]) {
                    selectedTowerTMP = new TowerHigh(550.0f, this->textureManager, this->soundManager, this->waveManager, this->player, 6, 180, 225);
                }

                this->selectedTowerTMP->setPosition(mousePos.x - selectedTowerTMP->sprite.getGlobalBounds().width / 2,
                    mousePos.y - selectedTowerTMP->sprite.getGlobalBounds().height / 2);

                if (this->map->canPlaceTower(gridX, gridY)) {
                    selectedTowerTMP->setPosition(gridX * map->getWidthTile(), gridY * map->getHeightTile());
                    this->selectedTowerTMP->isActive = true;
                    mapTowers.push_back(selectedTowerTMP);
                    selectedTowerTMP = nullptr; // Reset po umieszczeniu wie¿y
                    isTurretSelected = false;

                    this->soundManager->getSound("TowerBuy").play();
                }
            }
        }
    }
}

/// <summary>
/// Sprawdza czy przycisk myszki zosta³ wciœniety i puszczony
/// </summary>
/// <returns></returns>
const bool& GameplayUI::turretSelected() const
{
    return mouseLeftPressedLastFrame && !mouseLeftPressed;
}



std::vector<sf::Sprite>* GameplayUI::getTurretSprite()
{
    return &this->turretSprites;
}

bool GameplayUI::isTowerSelected() const
{
    return this->isTurretSelected;
}

void GameplayUI::initFont() {
    if (!this->font.loadFromFile("Resources/Fonts/04B_30__.ttf")) {
        std::cout << "Nie zaladowano fontu!!!\n";
    }
}

void GameplayUI::initTexts() {
    this->playerHealthText.setString("HP:");
    this->playerHealthText.setFont(this->font);
    this->playerHealthText.setCharacterSize(40);
    this->playerHealthText.setFillColor(sf::Color::Black);
    this->playerHealthText.setPosition(this->window->getSize().x * 0.018f, this->window->getSize().y * 0.742f);

    this->turretBuyMenuText.setString("Buy:");
    this->turretBuyMenuText.setFont(this->font);
    this->turretBuyMenuText.setCharacterSize(40);
    this->turretBuyMenuText.setFillColor(sf::Color::Black);
    this->turretBuyMenuText.setPosition(this->window->getSize().x * 0.25f, this->window->getSize().y * 0.742f);

    this->playerCoinsText.setString("Coins:");
    this->playerCoinsText.setFont(this->font);
    this->playerCoinsText.setCharacterSize(40);
    this->playerCoinsText.setFillColor(sf::Color::Black);
    this->playerCoinsText.setPosition(this->window->getSize().x * 0.5f, this->window->getSize().y * 0.742f);

    this->coinAmount.setString(std::to_string(this->player->getCoins()));
    this->coinAmount.setFont(this->font);
    this->coinAmount.setCharacterSize(40);
    this->coinAmount.setFillColor(sf::Color::Yellow);
    this->coinAmount.setPosition(this->window->getSize().x * 0.55f, this->window->getSize().y * 0.835f);

    sf::Text turretCost1("50", this->font, 20);
    turretCost1.setFillColor(sf::Color::Yellow);
    turretCost1.setPosition(this->window->getSize().x * 0.269f + 0 * 1.8f * this->map->getHeightTile(), (this->window->getSize().y * 0.9303f));
    this->turretCostText.push_back(turretCost1);

    sf::Text turretCost2("125", this->font, 20);
    turretCost2.setFillColor(sf::Color::Yellow);
    turretCost2.setPosition(this->window->getSize().x * 0.269f + 1 * 1.8f * this->map->getHeightTile(), (this->window->getSize().y * 0.9303f));
    this->turretCostText.push_back(turretCost2);

    sf::Text turretCost3("225", this->font, 20);
    turretCost3.setFillColor(sf::Color::Yellow);
    turretCost3.setPosition(this->window->getSize().x * 0.269f + 2 * 1.8f * this->map->getHeightTile(), (this->window->getSize().y * 0.9303f));
    this->turretCostText.push_back(turretCost3);
    
    this->waveNumberText.setString("Wave: ");
    this->waveNumberText.setFont(this->font);
    this->waveNumberText.setCharacterSize(40);
    this->waveNumberText.setFillColor(sf::Color::Black);
    this->waveNumberText.setPosition(this->window->getSize().x * 0.728f, this->window->getSize().y * 0.742f);

    this->waveNumber.setString(std::to_string(this->waveManager->getWaveNumber()));
    this->waveNumber.setFont(this->font);
    this->waveNumber.setCharacterSize(40);
    this->waveNumber.setFillColor(sf::Color::Black);
    this->waveNumber.setPosition(this->window->getSize().x * 0.84f, this->window->getSize().y * 0.809f);

    this->playerScore.setString(std::to_string(this->player->getScore()));
    this->playerScore.setFont(this->font);
    this->playerScore.setCharacterSize(40);
    this->playerScore.setFillColor(sf::Color::Black);
    this->playerScore.setPosition(this->window->getSize().x * 0.775f, this->window->getSize().y * 0.08f);

    this->scoreText.setString("Score:");
    this->scoreText.setFont(this->font);
    this->scoreText.setCharacterSize(40);
    this->scoreText.setFillColor(sf::Color::Black);
    this->scoreText.setPosition(this->window->getSize().x * 0.63f, this->window->getSize().y * 0.08f);

    this->startGameText.setString("Start");
    this->startGameText.setFont(this->font);
    this->startGameText.setCharacterSize(40);
    this->startGameText.setFillColor(sf::Color::Black);
    this->startGameText.setPosition(this->window->getSize().x * 0.728f, this->window->getSize().y * 0.742f);
}


void GameplayUI::initHealthSprites() {

    for (int i = 0; i < 5; ++i) {
        sf::Sprite sprite(this->textureManager->getTexture("HPfull")); 
        sprite.setPosition(this->window->getSize().x * 0.018f + i * 50, this->window->getSize().y * 0.81f);
        this->healthSprites.push_back(sprite);
    }
}

void GameplayUI::initTurretSprites()
{
    float scale = 1.8f;

    menuTowers[0]->sprite.setScale(scale, scale);
    menuTowers[0]->sprite.setPosition(this->window->getSize().x * 0.25f + 0 * 0 * this->map->getHeightTile(), (this->window->getSize().y * 0.683f) + this->map->getHeightTile() * scale);

    menuTowers[1]->sprite.setScale(scale, scale);
    menuTowers[1]->sprite.setPosition(this->window->getSize().x * 0.25f + 1 * scale * this->map->getHeightTile(), (this->window->getSize().y * 0.683f) + this->map->getHeightTile() * scale);

    menuTowers[2]->sprite.setScale(scale, scale);
    menuTowers[2]->sprite.setPosition(this->window->getSize().x * 0.25f + 2 * scale * this->map->getHeightTile(), (this->window->getSize().y * 0.683f) + this->map->getHeightTile() * scale);
}

void GameplayUI::initCoinSprite()
{
   sf::Sprite coin(this->textureManager->getTexture("Coin"));
   float spaceBtwn = 1.8f;
    coin.setScale(1.4f, 1.4f);
    for (size_t i = 0; i < 3; i++)
    {
        coin.setPosition(this->window->getSize().x * 0.25f + i * spaceBtwn * this->map->getHeightTile(), (this->window->getSize().y * 0.865f) + this->map->getHeightTile());
        this->coinSprite.push_back(coin);
    }
    coin.setScale(3.5f, 3.5f);
    coin.setPosition(this->window->getSize().x * 0.5f, this->window->getSize().y * 0.83f);
    this->coinSprite.push_back(coin);


}

void GameplayUI::initWaveSprite()
{
    this->waveIconSprite.setTexture(this->textureManager->getTexture("WaveIcon"));
    this->waveIconSprite.setScale(sf::Vector2f(2.3f,2.3f));
    this->waveIconSprite.setPosition(this->window->getSize().x * 0.745f, this->window->getSize().y * 0.8f);
}

void GameplayUI::checkWaveButton() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
    if (this->waveIconSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        if (!isHoveringIcon) {
            this->waveIconSprite.setScale(2.5f, 2.5f); // Powieksza
            isHoveringIcon = true;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (!this->waveManager->getWaveExists()) {
                this->waveManager->startNewWave();
                this->soundManager->getSound("NextWave").play();
            }
        }
    }
    else {
        if (isHoveringIcon) {
            this->waveIconSprite.setScale(2.3f, 2.3f); // Reset to original size
            isHoveringIcon = false;
        }
    }
}

void GameplayUI::update(const float& dt) {
    this->updateMousePos();
    this->updateMouseState();
    this->checkWaveButton();

    //Umieszczone wyzej, zeby po kupnie nie pokazywa³ sie domyslnie zasieg wiezy
    for (auto& tower : mapTowers) {
        tower->update(dt);
        if (turretSelected()) {
            tower->handleMouseInteraction(this->mousePos); 
        }
    }

    this->updateCoinAmount();
    this->updateHealth();
    this->buyTower();
    this->waveNumber.setString(std::to_string(this->waveManager->getWaveNumber())); //update wave amount
    this->playerScore.setString(std::to_string(this->player->getScore()));//update playerScore 



  
    // Anulowanie zakupu wie¿y
    if (this->isTurretSelected && this->RightMouseClick()) {
        this->soundManager->getSound("Cancel").play();
        this->isTurretSelected = false;
        this->selectedTowerTMP = nullptr;
        this->player->increaseCoins(this->selectedTower->getTowerCost()); // Zwrócenie kosztu wie¿y graczowi
    }
}

void GameplayUI::render(sf::RenderTarget* target) {
    // Rysowanie tekstu dotycz¹cego monet
    target->draw(this->playerCoinsText);
    target->draw(this->playerHealthText);
    target->draw(this->turretBuyMenuText);
    target->draw(this->coinAmount);
    if (this->waveManager->getWaveExists() == false) {
        this->startGameText.setFillColor(sf::Color::Yellow);
        target->draw(this->startGameText);
    }
    else {
        target->draw(this->waveNumberText);

    }
    target->draw(this->waveNumber);

    for (auto& turretCost : this->turretCostText)
    {
        target->draw(turretCost);
    }

    // Rysowanie grafik serc
    for (auto& health : this->healthSprites) {
        target->draw(health);
    }
    for (auto& turret: this->turretSprites) {
        target->draw(turret);
    }

    for (auto& coin : this->coinSprite) {
        target->draw(coin);
    }

    for (auto& tower : this->menuTowers) {
        tower->render(this->window);
    }
    for (auto& tower : this->mapTowers) {
        tower->render(this->window);
    }

    target->draw(this->waveIconSprite);

    //Umieszczenie wiezy przy kursorze
    if (selectedTowerTMP != nullptr) {
        selectedTowerTMP->sprite.setPosition(mousePos.x - selectedTowerTMP->sprite.getGlobalBounds().width / 2,
            mousePos.y - selectedTowerTMP->sprite.getGlobalBounds().height / 2);
        target->draw(selectedTowerTMP->sprite);
    }
    target->draw(this->playerScore);
    target->draw(this->scoreText);

  }

//u¿ywane do debugowania
const TextureManager* GameplayUI::getTxtMan()
{
    return this->textureManager;
}
