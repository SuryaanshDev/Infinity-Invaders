#include <iostream>
#include "include/GameOver.h"

GameOver:: GameOver()
	: m_GameOverSprite(m_GameOverTexture), m_IsGameOver(false)
{
}

GameOver:: ~GameOver()
{
}

void GameOver::Update(Menu& menu)
{

    if (IsGameOver()) {
        
        static bool m_EscPressed = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            
            if (!m_EscPressed && m_IsGameOver) {
                
                m_EscPressed = true;
                m_IsGameOver = false;
                menu.SetInMenu(true);
            }
        }

        else {
            m_EscPressed = false;
        }
    }
}

void GameOver:: Load()
{
	
    if (!m_GameOverTexture.loadFromFile("resources/Game_Over.jpg")) {

        std::cerr << "Unable to load gameOver texture!" << std::endl;
    }

    else {

        std::cout << "Game over textures loaded successfully :)" << std::endl;
    }

    m_GameOverSprite.setTexture(m_GameOverTexture);
    m_GameOverSprite.setTextureRect(sf::IntRect({ 0, 0 }, {1920, 1080}));
}

void GameOver:: Draw(sf::RenderWindow& window) 
{
    
    window.draw(m_GameOverSprite);
}

bool GameOver:: IsGameOver() {

	return m_IsGameOver;
}

void GameOver::SetGameOver(bool set)
{

    m_IsGameOver = set;
}
