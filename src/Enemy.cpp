#include "include/Enemy.h"
#include <iostream>

Enemy::Enemy()
	:m_EnemySpeed(0), m_EnemyHealth(5), m_EnemySprite(m_EnemyTexture)
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	
	m_EnemySprite.setScale({4, 4});
	m_EnemySprite.setPosition({400, 300});
}

void Enemy::Load()
{
	int xIndex = 0;
	int yIndex = 0;

	int m_Width = 32;
	int m_Height = 32;

	if (!m_EnemyTexture.loadFromFile("resources/UFO.png")) {
		
		std::cerr << "Failed to load Enemy Textures" << std::endl;
	}

	else {

		std::cout << "Enemy textures loaded successfully :)";
	}

	m_EnemySprite.setTexture(m_EnemyTexture);
	sf::IntRect spriteRect({ xIndex * m_Width, yIndex * m_Width }, { m_Width , m_Height });
	m_EnemySprite.setTextureRect(spriteRect);
}

void Enemy::Update(double deltaTime)
{
}

void Enemy::Draw(sf::RenderWindow& window)
{

	window.draw(m_EnemySprite);
}