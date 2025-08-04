#pragma once
#include <SFML/Graphics.hpp>
#include "include/Menu.h"

class GameOver {

private:
	
	bool m_IsGameOver;
	sf::Texture m_GameOverTexture;
	sf::Sprite m_GameOverSprite;

public:

	GameOver();
	~GameOver();
	
	void Update(Menu& menu);
	void Load();
	void Draw(sf::RenderWindow& window);
	bool IsGameOver();
	void SetGameOver(bool set);
};