#pragma once
#include <SFML/Graphics.hpp>

class Bullet {

private:
	
	float m_BulletSpeed;
	sf::RectangleShape m_Bullet;
	sf::Vector2f offset;
public:

	Bullet();
	~Bullet();
	void Load();
	void Update(double deltaTime);
	void Initialize(const sf::Vector2f& position);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f GetPosition();
};