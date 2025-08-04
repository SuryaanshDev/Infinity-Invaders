#include <iostream>
#include "include/GameOver.h"
#include <sstream>
#include <iomanip>

GameOver::GameOver()
    : m_GameOverSprite(m_GameOverTexture), m_IsGameOver(false), m_CurrentScore(0),
    m_ScoreText(m_ScoreFont), m_HighscoreText(m_ScoreFont), m_RankText(m_ScoreFont),
    m_InstructionText(m_ScoreFont), m_NewHighscoreText(m_ScoreFont), m_IsNewHighscore(false)
{
}

GameOver::~GameOver()
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

void GameOver::Load()
{
    if (!m_GameOverTexture.loadFromFile("resources/Game_Over.jpg")) {
        std::cerr << "Unable to load gameOver texture!" << std::endl;
    }
    else {
        std::cout << "Game over textures loaded successfully :)" << std::endl;
    }

    m_GameOverSprite.setTexture(m_GameOverTexture);
    m_GameOverSprite.setTextureRect(sf::IntRect({ 0, 0 }, { 1920, 1080 }));

    if (!m_ScoreFont.openFromFile("resources/ScoreFont.ttf")) {
        std::cerr << "Score font not found for game over screen!" << std::endl;
    }
    else {
        std::cout << "Score font loaded for game over screen :)" << std::endl;
    }

    InitializeTexts();
}

void GameOver::Draw(sf::RenderWindow& window)
{
    window.draw(m_GameOverSprite);

    window.draw(m_ScoreText);
    window.draw(m_HighscoreText);
    window.draw(m_RankText);
    window.draw(m_InstructionText);

    if (m_IsNewHighscore) {
        window.draw(m_NewHighscoreText);
    }
}

bool GameOver::IsGameOver() {
    return m_IsGameOver;
}

void GameOver::SetGameOver(bool set)
{
    m_IsGameOver = set;
}

void GameOver::SetScore(int score, Highscoremanager& highscoreManager)
{
    m_CurrentScore = score;

    m_IsNewHighscore = highscoreManager.IsNewHighscore(score);

    if (score > 0) { 
        highscoreManager.AddScores(score);
    }

    UpdateScoreTexts(highscoreManager);
}

void GameOver::InitializeTexts()
{
    m_ScoreText.setFont(m_ScoreFont);
    m_ScoreText.setCharacterSize(48);
    m_ScoreText.setFillColor(sf::Color::White);
    m_ScoreText.setPosition({ 960 - 200, 700 }); 

    m_HighscoreText.setFont(m_ScoreFont);
    m_HighscoreText.setCharacterSize(48);
    m_HighscoreText.setFillColor(sf::Color::Yellow);
    m_HighscoreText.setPosition({ 960 - 200, 800 });

    m_RankText.setFont(m_ScoreFont);
    m_RankText.setCharacterSize(36);
    m_RankText.setFillColor(sf::Color::Cyan);
    m_RankText.setPosition({960 - 150, 900});

    m_InstructionText.setFont(m_ScoreFont);
    m_InstructionText.setCharacterSize(24);
    m_InstructionText.setFillColor(sf::Color::White);
    m_InstructionText.setString("Press ESC to return to menu");
    m_InstructionText.setPosition({ 700 , 300 });

    m_NewHighscoreText.setFont(m_ScoreFont);
    m_NewHighscoreText.setCharacterSize(60);
    m_NewHighscoreText.setFillColor(sf::Color::Red);
    m_NewHighscoreText.setString("NEW HIGHSCORE!");
    m_NewHighscoreText.setPosition({960 - 250, 600});
}

void GameOver::UpdateScoreTexts(Highscoremanager& highscoreManager)
{
    m_ScoreText.setString("Your Score: " + std::to_string(m_CurrentScore));

    int highscore = highscoreManager.GetHighscore();
    m_HighscoreText.setString("Best Score: " + std::to_string(highscore));

    int rank = highscoreManager.GetRank(m_CurrentScore);
    if (rank > 0) {
        std::string rankSuffix;
        if (rank == 1) rankSuffix = "st";
        else if (rank == 2) rankSuffix = "nd";
        else if (rank == 3) rankSuffix = "rd";
        else rankSuffix = "th";

        m_RankText.setString("Rank: " + std::to_string(rank) + rankSuffix + " place!");
        m_RankText.setFillColor(sf::Color::Green);
    }
    else {
        m_RankText.setString("Not in top 10");
        m_RankText.setFillColor(sf::Color::Yellow);
    }
}
