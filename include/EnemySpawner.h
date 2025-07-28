#pragma once
#include <vector>
#include <memory>
#include "include/Enemy.h"

class EnemySpawner {

private:
	
	std::vector<std::unique_ptr<Enemy>> enemies;
	float m_SpawnTimer;
	float m_SpawnCooldown;

public:
	
	EnemySpawner();
	~EnemySpawner();

	void Update(double deltaTime);
	void Draw(sf::RenderWindow& window);
};