#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "include/Player.h"
#include "include/Enemy.h"
#include "include/EnemySpawner.h"
#include "include/HUD.h"
#include "include/Menu.h"
#include "include/GameOver.h"
#include "include/GameState.h"
#include "include/HighScoreManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1920u, 1080u }), "GameCpp");
    window.setFramerateLimit(60);

    //---------------GameState----------------
    GameState state = GameState::MENU;

    // Player
    Player Plane(32, 32, 20.0f);
    Plane.SetScreenDimensions(1920, 1080); 
    Plane.Load();
    Plane.Initialize();

    // Music
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("resources/audio/Vibe1.mp3"))
        std::cerr << "Failed to load music!\n";
    else {
        std::cout << "Music loaded successfully :)\n";
        backgroundMusic.setLooping(true);
        backgroundMusic.setVolume(50.0f);
        backgroundMusic.play();
    }

    // Menu
    Menu menu;

    // Instructions texture
    sf::Texture instructTextures;
    if (!instructTextures.loadFromFile("resources/Instructions.jpg"))
        std::cerr << "Failed to load Instructions textures!\n";
    else
        std::cout << "Loaded the Instructions textures Successfully :)\n";
    sf::Sprite instruct(instructTextures);

    // HUD
    Hud hud;
    hud.Load();
    hud.Initialize();
    hud.SetPosition({ 10, 10 });
    hud.SetScale({ 2, 2 });

    // Map
    sf::Texture mapTexture;
    if (!mapTexture.loadFromFile("resources/space.jpg"))
        std::cerr << "Unable to load map file!\n";
    else
        std::cout << "Map textures loaded successfully :)\n";
    sf::Sprite map(mapTexture);

    // GameOver screen
    GameOver gameOver;
    gameOver.Load();

    sf::Clock clock;

    // Enemy spawner
    EnemySpawner spawner;
    spawner.Initialize();

    //Highscores
    Highscoremanager highscoreManager("highscores.txt");

    // Main loop
    while (window.isOpen())
    {
        try {

            sf::Time deltaTimeTimer = clock.restart();
            double deltaTime = deltaTimeTimer.asSeconds();

            // Event handling 
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    window.close();

                if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                {
                    
                    if (keyPressed->code == sf::Keyboard::Key::Escape)
                    {
                        switch (state)

                        {

                        case (GameState::PLAYING):

                            backgroundMusic.stop();
                            gameOver.SetGameOver(true);
                            state = GameState::GAME_OVER;
                            break;

                        case (GameState::INSTRUCTIONS):

                            state = GameState::MENU;
                            menu.SetInMenu(true);
                            break;

                        case (GameState::GAME_OVER):

                            state = GameState::MENU;
                            menu.SetInMenu(true);
                            gameOver.SetGameOver(false);
                            break;

                        default:
                            break;
                        }
                    }
                }
            }

            // Game State Updates
            switch (state)
            {
            case GameState::MENU:
                menu.Update();
                menu.Pressed();
                if (menu.IsPlayPressed())
                {
                    backgroundMusic.stop();
                    gameOver.SetGameOver(false);
                    spawner.Reset();
                    Plane.Reset();
                    hud.Reset();

                    try {
                        spawner.Initialize();
                        Plane.Initialize();
                    }
                    catch (const std::exception& e) {
                        std::cerr << "Error during initialization: " << e.what() << std::endl;
                    }
                    menu.ClearSelection();

                    backgroundMusic.play();
                    state = GameState::PLAYING;
                }
                else if (menu.IsInstructionsPressed())
                {
                    state = GameState::INSTRUCTIONS;
                    menu.ClearSelection();
                }
                break;

            case GameState::PLAYING:
                Plane.Update(deltaTime, spawner);
                spawner.Update(deltaTime);
                hud.Update(deltaTime, Plane);
                if (Plane.IsDead())
                {
                    backgroundMusic.stop();
                    gameOver.SetScore(Plane.GetScore(), highscoreManager);
                    gameOver.SetGameOver(true);
                    state = GameState::GAME_OVER;
                }
                break;

            case GameState::GAME_OVER:
                gameOver.Update(menu);
                if (!gameOver.IsGameOver())
                {
                    state = GameState::MENU;
                    menu.SetInMenu(true);
                    menu.ClearSelection();
                }
                break;

            case GameState::INSTRUCTIONS:
                std::cout << "DEBUG: In instructions state" << std::endl;
                break;

            default:
                break;
            }

            // Rendering
            window.clear();
            switch (state)
            {
            case GameState::PLAYING:
                window.draw(map);
                Plane.Draw(window);
                spawner.Draw(window);
                hud.Draw(window);
                break;

            case GameState::GAME_OVER:
                gameOver.Draw(window);
                break;

            case GameState::MENU:
                menu.Draw(window);
                break;

            case GameState::INSTRUCTIONS:
                window.draw(instruct);
                break;

            default:
                break;
            }
            window.display();
        }

        catch (...) {
            std::cerr << "ERROR: Unknown exception caught!" << std::endl;
            std::cerr << "Current state: " << static_cast<int>(state) << std::endl;
            break;
        }
    }

    return 0;
}
