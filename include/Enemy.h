#pragma once
#include<SFML/Graphics.hpp>

class Enemy {
	
private:
	float m_EnemySpeed;
	int m_EnemyHealth;
	sf::Texture m_EnemyTexture;
	sf::Sprite m_EnemySprite;
public:
	
	Enemy();
	~Enemy();

	void Initialize();
	void Load();
	void Update(double deltaTime);
	void Draw(sf::RenderWindow& window);

// Getters and Setters 
public:
	void SetSpeed(float speed);
	void SetPosition(const sf::Vector2f& pos);
	sf::Vector2f GetPosition() const;
};