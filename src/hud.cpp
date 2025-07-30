#include "include/HUD.h"
#include <iostream>

Hud::Hud()
	: m_HealthSprite(m_HealthTexture), m_CurrentHealth(3), m_Score(0)
{
}

Hud::~Hud()
{
}

void Hud::Load()
{

	if (!m_HealthTexture.loadFromFile("resources/Heart.png")) {

		std::cerr << "Health Textures not found!" << std::endl;
	}

	else {

		std::cout << "Health Textures found successfully :)" << std::endl;
	}
	
	for (int i = 0; i < m_CurrentHealth; i++) {
		
		sf::Sprite heart(m_HealthTexture);
		heart.setTextureRect(sf::IntRect({ 0 * 32, 0 * 32 }, { 32, 32 }));

		m_Health.push_back(heart);
		
		for (int i = 0; i < m_CurrentHealth; i++) {
	
			heart.setScale({ 2, 2 });
		}
	}
}

void Hud::Initialize()
{

}

void Hud::SetPosition(sf::Vector2f pos)
{
	for (int i = 0; i < m_CurrentHealth; i++) {

		m_Health[i].setPosition(pos + sf::Vector2f((float)i * 70.f, 0));
	}
}

void Hud::SetScale(sf::Vector2f scale)
{

	for (int i = 0; i < m_CurrentHealth; i++) {
		
		m_Health[i].setScale(scale);
	}
}

void Hud::Update(double deltaTime, Player& player) 
{
}

void Hud::Draw(sf::RenderWindow& window)
{

	for (int i = 0; i < m_CurrentHealth; i++) {

		window.draw(m_Health[i]);
	}
}

void Hud::SetScore()
{
		
} 