#include "include/HUD.h"
#include <iostream>

Hud::Hud()
	: m_HealthSprite(m_HealthTexture), m_CurrentHealth(3), m_CurrentScore(0), m_ScoreText(m_ScoreFont)

{
}

Hud::~Hud()
{
}

void Hud::Load()
{
// -------------------Loading Score Font----------------------------------------
	if (!m_ScoreFont.openFromFile("resources/ScoreFont.ttf")) {
		
		std::cerr << "Score font not found!" << std::endl;
	}

	else {

		std::cout << "Score font loaded successfully :)" << std::endl;
	}

	m_ScoreText.setFont(m_ScoreFont);
	
//-------------------------------------------------------------------------------------

// -------------------------Loading Heart textures and sprite--------------------------	
	if (!m_HealthTexture.loadFromFile("resources/Heart.png")) {

		std::cerr << "Health Textures not found!" << std::endl;
	}

	else {

		std::cout << "Health Textures found successfully :)" << std::endl;
	}

	for (int i = 0; i < m_CurrentHealth; i++) {
		
		sf::Sprite heart(m_HealthTexture);
		heart.setTextureRect(sf::IntRect({ 0, 0 }, { 32, 32 }));

		m_Health.push_back(heart);
	}

	
//-----------------------------------------------------------------------------------------	
}

void Hud::Initialize()
{

	m_ScoreText.setPosition({1700, 10});
	m_ScoreText.setFillColor(sf::Color::Green);
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

	int newHealth = player.GetHealth();

	if (newHealth != m_CurrentHealth) {
		
		m_CurrentHealth = newHealth;

		m_Health.clear();

		for (int i = 0; i < m_CurrentHealth; i++) {
			
			sf::Sprite heart(m_HealthTexture);
			heart.setTextureRect(sf::IntRect({ 0, 0 }, { 32, 32 }));
			m_Health.push_back(heart);
		}

		SetPosition({10.0f, 10.0f});
		SetScale({2, 2});
	}
	
	SetScore(player.GetScore());
	
	m_ScoreText.setString("Score: " + std::to_string(m_CurrentScore));
}

void Hud::Draw(sf::RenderWindow& window)
{

	for (int i = 0; i < m_CurrentHealth; i++) {

		window.draw(m_Health[i]);
	}

	window.draw(m_ScoreText);
}

void Hud::SetScore(int score)
{
	m_CurrentScore = score;
} 