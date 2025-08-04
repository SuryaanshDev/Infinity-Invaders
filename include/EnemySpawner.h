#pragma once
#include <vector>
#include <memory>
#include "include/Enemy.h"
#include <SFML/Audio.hpp>

class EnemySpawner {

private:
	
	std::vector<std::unique_ptr<Enemy>> enemies;
	float m_SpawnTimer;
	float m_SpawnCooldown;
	
	sf::SoundBuffer m_EnemyDeathBuffer;
	sf::Sound m_EnemyDeathSound;

	bool m_SoundLoaded;

public:
	
	EnemySpawner();
	~EnemySpawner();

	void Update(double deltaTime);
	void Draw(sf::RenderWindow& window);
	void Initialize();
	std::vector<std::unique_ptr<Enemy>>& GetEnemies();

	void Reset();
};