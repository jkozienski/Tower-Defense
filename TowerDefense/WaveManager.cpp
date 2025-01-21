#include "WaveManager.h"

// Konstruktor
WaveManager::WaveManager(Map* map, Player* player) : map(map),player(player) {
    this->waveExists = false;
}


WaveManager::~WaveManager() {

    std::ranges::for_each(waves | std::views::join, [](Enemy* enemy) {
        delete enemy;
        });
    
}

const bool& WaveManager::getWaveExists() const
{
    return this->waveExists;
}

// Metoda do generowania pojedynczej fali
void WaveManager::generateWave(int minEasy, int maxEasy, int minMedium, int maxMedium, int minHard, int maxHard) {
    enemiesInWave.clear();

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distEasy(minEasy + this->currentWaveNumber, maxEasy + this->currentWaveNumber);
    std::uniform_int_distribution<> distMedium(minMedium + this->currentWaveNumber, maxMedium + this->currentWaveNumber);
    std::uniform_int_distribution<> distHard(minHard + this->currentWaveNumber, maxHard + this->currentWaveNumber);

    int numEasy = distEasy(gen);
    int numMedium = distMedium(gen);
    int numHard = distHard(gen);

    int hpMid= 30;
    int hpEasy= 25;
    int hpHard = 38;
    float speed=0.08f;

    if (this->currentWaveNumber % 3 == 0) {
        speed += 0.035f;

        hpMid += this->currentWaveNumber*1.2f;
        hpEasy += this->currentWaveNumber * 1.2f;
        hpHard += this->currentWaveNumber * 1.2f;
       // std::cout << hpMid << " " << hpEasy << " " << hpHard << "\n";
        
    }

    sf::Vector2f offset = sf::Vector2f(100.f, 0.f);
    sf::Vector2f currEnemyMidPos;
    for (int i = 0; i < numMedium; ++i) {
        currEnemyMidPos = sf::Vector2f(map->getHeightTile() * 1.25f * -i, map->getWidthTile() * 2) - offset;
        Enemy* enemyMedium = new EnemyMedium(currEnemyMidPos, hpMid, 100, 10, 0.08f, 9, 75, this->map, this->textureManager, this->player);

        this->enemiesInWave.push_back(enemyMedium);
    }

    sf::Vector2f currEnemyEasyPos;
    for (int i = 1; i <= numEasy; ++i) {
        currEnemyEasyPos = currEnemyMidPos + sf::Vector2f(map->getHeightTile() * 1.5f * -i, 0.f);
        Enemy* enemyEasy = new EnemyEasy(currEnemyEasyPos, hpEasy, 10, 10, 0.08f, 5, 50, this->map, this->textureManager, this->player);
        this->enemiesInWave.push_back(enemyEasy);
    }

    sf::Vector2f currEnemyHardPos;
    for (int i = 1; i <= numHard; ++i) {
        currEnemyHardPos = currEnemyEasyPos + sf::Vector2f(map->getHeightTile() * 1.5f * -i, 0.f);

        Enemy* enemyHard = new EnemyHard(currEnemyHardPos, hpHard, 100, 10, 0.08f, 16, 100, this->map, this->textureManager, this->player);
        this->enemiesInWave.push_back(enemyHard);
    }
    this->waves.push_back(enemiesInWave);
    this->waveExists = true;
    //std::cout << "Rozmiar fali:" << this->enemiesInWave.size() << "\n";

}

const std::vector<std::vector<Enemy*>>& WaveManager::getWaves() const
{
    return this->waves;
}


 const std::vector<Enemy*>& WaveManager::getEnemies() const
{
    return this->enemiesInWave;
}

// Metoda do rozpoczêcia nowej fali
void WaveManager::startNewWave() {
    if (this->waveExists==false) {
        this->currentWaveNumber++;
        //std::cout << "Wave number: " << currentWaveNumber << "\n";
        this->generateWave(2,3,1,2,0,2);
        this->waveExists = true;
    }
}


void WaveManager::update(const float& dt) {
    if (!waves.empty()) {
        for (auto& enemy : waves | std::views::join) {
            enemy->update(dt);
        }

        // Usuwanie przeciwników poza pêtl¹ g³ówn¹
        for (auto& wave : waves) {
            wave.erase(
                std::remove_if(wave.begin(), wave.end(), [](Enemy* enemy) {
                    if (!enemy->getAlive() || enemy->getFinished()) {
                        delete enemy;
                        return true;
                    }
                    return false;
                    }),
                wave.end()
            );
        }

        // Usuwanie pustych fal
        waves.erase(
            std::remove_if(waves.begin(), waves.end(), [](const std::vector<Enemy*>& wave) {
                return wave.empty();
                }),
            waves.end()
        );
    }
    if (waves.empty()) {
        waveExists = false;
    }
}

const int WaveManager::getWaveNumber()
{
    return this->currentWaveNumber;
}

void WaveManager::render(sf::RenderTarget* target)
{
    
    if (!waves.empty()) {
        for (const auto& enemy : waves | std::views::join) {
            enemy->render(target);
        }
    }
}

