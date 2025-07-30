#include "include/Enemy.h"
#include <iostream>
#include "include/Math.h"

Enemy::Enemy()
	:m_EnemySpeed(300.0f), m_EnemyHealth(5), m_EnemySprite(m_EnemyTexture)
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	
	m_EnemySprite.setScale({4, 4});
	m_EnemySprite.setPosition({400, 300});

	m_BoundingRectangle.setFillColor(sf::Color::Transparent);
	m_BoundingRectangle.setOutlineColor(sf::Color::Red);
	m_BoundingRectangle.setOutlineThickness(1);
	m_BoundingRectangle.setScale({4, 4});
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

	m_BoundingRectangle.setSize({m_Width * m_EnemySprite.getScale().x,
								m_Height * m_EnemySprite.getScale().y});

}

void Enemy::Update(double deltaTime)
{

	m_EnemySprite.move({ 0, m_EnemySpeed * static_cast<float>(deltaTime) });
	
	m_BoundingRectangle.setPosition(m_EnemySprite.getPosition());
}

void Enemy::Draw(sf::RenderWindow& window)
{

	window.draw(m_EnemySprite);
	window.draw(m_BoundingRectangle);
}

void Enemy::SetSpeed(float speed)
{
	m_EnemySpeed = speed;
}

void Enemy::SetPosition(const sf::Vector2f& pos)
{

	m_EnemySprite.setPosition(pos);
}

sf::Vector2f Enemy::GetPosition() const
{

	return	m_EnemySprite.getPosition();
}

int Enemy::GetHealth() const {

	return m_EnemyHealth;
}

void Enemy::SetHealth(int hp)
{
	m_EnemyHealth += hp;
}

sf::FloatRect Enemy::GetBounds() const{

	return m_EnemySprite.getGlobalBounds();
}
