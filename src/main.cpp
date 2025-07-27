#include <SFML/Graphics.hpp>
#include "include/Player.h"
#include <iostream>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "GameCpp");
    window.setFramerateLimit(60);
// --------------Initializing and loading player---------------- 
    Player Plane(32, 32, 20.0f);
    Plane.Load();
    Plane.Initialize();
// ------------------------------------------------------------

//----------------- Loading and setting map--------------------
    sf::Texture mapTexture;
    
    if (!mapTexture.loadFromFile("resources/space.jpg")) {
        
        std::cerr << "Unable to load file!" << std::endl;
    }

    else {

        std::cout << "Textures loaded successfully :)";
    }
    
    sf::Sprite map(mapTexture);
//-----------------------------------------------------------------
    sf::Clock clock;


    while (window.isOpen())
    {
        sf::Time deltaTimeTimer = clock.restart();
        double deltaTime = deltaTimeTimer.asSeconds();

        Plane.Update(deltaTime);

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        
        window.clear();
        window.draw(map);
        Plane.Draw(window);
        window.display();
    }
}
