#include <SFML/Graphics.hpp>
#include "include/Player.h"
#include <iostream>
#include "include/Enemy.h"
#include "include/EnemySpawner.h"
#include "include/HUD.h"
#include <SFML/Audio.hpp>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "GameCpp");
    window.setFramerateLimit(60);
// --------------Initializing and loading player---------------- 
    Player Plane(32, 32, 20.0f);
    Plane.Load();
    Plane.Initialize();
// ------------------------------------------------------------
// -----------------------------Music--------------------------
    sf::Music backgroundMusic;

    if (!backgroundMusic.openFromFile("resources/audio/Vibe1.mp3")) {
           
        std::cerr << "Failed to load music!" << std::endl;
    }

    else {
        
        std::cout << "Music loaded successfully :)" << std::endl;
        backgroundMusic.setLooping(true);
        backgroundMusic.setVolume(50.0f);
        backgroundMusic.play();
    }

//------------------------------------------------------------- 
//------------------Initializing and loading the HUD-----------
    Hud hud;
    hud.Load();
    hud.Initialize();
    hud.SetPosition({10, 10});
    hud.SetScale({2, 2});
//------------------------------------------------------------- 
//----------------- Loading and setting map--------------------
    sf::Texture mapTexture;
    
    if (!mapTexture.loadFromFile("resources/space.jpg")) {
        
        std::cerr << "Unable to load file!" << std::endl;
    }

    else {

        std::cout << "Map textures loaded successfully :)" << std::endl;
    }
    
    sf::Sprite map(mapTexture);

    sf::Texture gameOverTexture;

    if (!gameOverTexture.loadFromFile("resources/Game_Over.jpg")) {
        
        std::cerr << "Unable to load gameOver texture!" << std::endl;
    }

    else {

        std::cout << "Game over textures loaded successfully :)" << std::endl;
    }

    sf::Sprite gameOver(gameOverTexture);
 
//-----------------------------------------------------------------
    sf::Clock clock;

//--------------Initializing and loading Enemy---------------------
    EnemySpawner spawner;
    spawner.Initialize();
//----------------------------------------------------------------
    while (window.isOpen())
    {
        sf::Time deltaTimeTimer = clock.restart();
        double deltaTime = deltaTimeTimer.asSeconds();
        
        if (!Plane.IsDead()) {

            Plane.Update(deltaTime, spawner);

            spawner.Update(deltaTime);
        }

        hud.Update(deltaTime, Plane);

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        
        window.clear();

        if (!Plane.IsDead()) {
            
            window.draw(map);
            Plane.Draw(window);
            spawner.Draw(window);
            hud.Draw(window);
        }

        else {

            window.draw(gameOver);
            backgroundMusic.stop();
        }

        window.display();
    }
}
