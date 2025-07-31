#pragma once
#include<SFML/Graphics.hpp>
#include <vector>
#include "include/Player.h"

class Hud {

private:

	sf::Texture m_HealthTexture;
	sf::Sprite m_HealthSprite;
	std::vector<sf::Sprite> m_Health;
	int m_CurrentHealth;

private:

	sf::Font m_ScoreFont;
	sf::Text m_ScoreText;
	int m_CurrentScore;

public:

	Hud();
	~Hud();

	void Load();
	void Initialize();
	void SetPosition(sf::Vector2f pos);
	void SetScale(sf::Vector2f scale);
	void Update(double deltaTime, Player& player);
	void Draw(sf::RenderWindow& window);
	void SetScore(int score);
};