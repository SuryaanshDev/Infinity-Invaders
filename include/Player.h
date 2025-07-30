#pragma once
#include <SFML/Graphics.hpp>
#include "include/Bullet.h"
#include "include/EnemySpawner.h"

class Player {

private: 
	
	int m_PlayerWidth;
	int m_PlayerHeight;
	float m_PlayerSpeed;
	int m_PlayerHealth;

	sf::Texture m_PlayerTexture;

	sf::Sprite m_PlayerSprite;

	std::vector<std::unique_ptr<Bullet>> bullets;

	float m_FireCooldown;

	float m_FireTimer;

public:
	
	Player(int width, int height, float speed);
	~Player();
	void Initialize();
	void Load();
	void Update(double deltaTime, EnemySpawner& spawner);
	void Draw(sf::RenderWindow& window);
	int GetHealth() const;
private:

	void Move();
};