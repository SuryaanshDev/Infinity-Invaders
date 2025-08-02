#pragma once
#include <SFML/Graphics.hpp>
#include "include/Bullet.h"
#include "include/EnemySpawner.h"
#include "include/Enemy.h"

class Player {

private: 
	
	int m_PlayerWidth;
	int m_PlayerHeight;
	float m_PlayerSpeed;
	int m_PlayerHealth;

	int m_PlayerScore;

private:

	sf::Texture m_PlayerTexture;

	sf::Sprite m_PlayerSprite;

	std::vector<std::unique_ptr<Bullet>> bullets;

private:

	float m_FireCooldown;

	float m_FireTimer;
	
	float m_DamageCooldown;
	float m_DamageTimer;

	bool m_IsDead;

public:
	
	Player(int width, int height, float speed);
	~Player();
	void Initialize();
	void Load();
	void Update(double deltaTime, EnemySpawner& spawner);
	void Draw(sf::RenderWindow& window);

public:

	int GetHealth() const;
	void TakeDamage(int dmg);
	
	int GetScore() const;
	bool IsDead();

private:

	void Move();
	void SetScore(int score);
};