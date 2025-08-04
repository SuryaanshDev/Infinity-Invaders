#pragma once
#include <SFML/Graphics.hpp>
#include "include/Menu.h"
#include "include/HighScoreManager.h"

class GameOver {

private:
	
	bool m_IsGameOver;
	sf::Texture m_GameOverTexture;
	sf::Sprite m_GameOverSprite;
	
	int m_CurrentScore;
	bool m_IsNewHighscore;

	sf::Font m_ScoreFont;
	sf::Text m_ScoreText;
	sf::Text m_HighscoreText;
	sf::Text m_RankText;
	sf::Text m_InstructionText;
	sf::Text m_NewHighscoreText;

	void InitializeTexts();
	void UpdateScoreTexts(Highscoremanager& highscoreManager);


public:

	GameOver();
	~GameOver();
	
	void Update(Menu& menu);
	void Load();
	void Draw(sf::RenderWindow& window);
	bool IsGameOver();
	void SetGameOver(bool set);

	void SetScore(int score, Highscoremanager& highscoreManager);
};