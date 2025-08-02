#include "include/EnemySpawner.h"
#include <iostream>

EnemySpawner::EnemySpawner()
: m_SpawnTimer(0.0f), m_SpawnCooldown(2.0f), m_EnemyDeathSound(m_EnemyDeathBuffer)
{
}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::Initialize() {
	
	if (!m_EnemyDeathBuffer.loadFromFile("resources/audio/E_Death.wav")) {

		std::cerr << "Failed to load sound!" << std::endl;
	}

	else {

		std::cout << "Death sound loaded successfully :)" << std::endl;
	}

	m_EnemyDeathSound.setBuffer(m_EnemyDeathBuffer);	
}

void EnemySpawner::Update(double deltaTime) 
{
	m_SpawnTimer += deltaTime;

	if (m_SpawnTimer >= m_SpawnCooldown) {
		
		auto enemy = std::make_unique<Enemy>();

		enemy->Load();
		enemy->Initialize();

		//Setting random spawn position
		float x = static_cast<float>(rand() % 1800 + 60);

		enemy->SetPosition(sf::Vector2f({x, -100.0f}));
		enemy->SetSpeed(500.0f);

		enemies.push_back(std::move(enemy));
		m_SpawnTimer = 0.0f;
	}

	//Updating all enemies
	for (auto& enemy : enemies) {
		
		enemy->Update(deltaTime);
	}

	enemies.erase(
		std::remove_if(enemies.begin(), enemies.end(),[this](const std::unique_ptr<Enemy>& e) {
				
			if (e->GetHealth() <= 0) {
				
				m_EnemyDeathSound.play();
				return true;
			}

			if (e->GetPosition().y > 1100) {
				
				return true;
			}

			return false;
		}),
		enemies.end()
	);
}

void EnemySpawner::Draw(sf::RenderWindow& window)
{

	for (auto& enemy : enemies) {
		
		enemy->Draw(window);
	}
}

std::vector<std::unique_ptr<Enemy>>& EnemySpawner::GetEnemies()
{

	return enemies;
}

